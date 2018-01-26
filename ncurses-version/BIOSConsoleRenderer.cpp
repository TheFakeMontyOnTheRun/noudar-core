/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/
#include <go32.h>
#include <conio.h>
#include <dpmi.h>
#include <pc.h>
#include <bios.h>
#include <time.h>
#include <unistd.h>
#include <sys/farptr.h>
#include <sys/movedata.h>
#include <sys/nearptr.h>

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <functional>
#include <algorithm>
#include <string>
#include <utility>
#include <map>
#include <memory>
#include <EASTL/vector.h>
#include <EASTL/array.h>

using eastl::vector;
using eastl::array;

#include "Common.h"
#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "CDoorway.h"
#include "CCharacterArchetype.h"
#include "CCharacter.h"
#include "CMonster.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"
#include "CGame.h"
#include "CConsoleRenderer.h"

namespace Knights {
    int col = 0;
    int row = 0;
    static const char directions[4] = { '^', '>', 'V', '<'};
    char ch = 0;
    uint8_t currAttrib = 0;
    enum EColor{
        COLOR_BLACK,
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_CYAN,
        COLOR_RED,
        COLOR_MAGENTA,
        COLOR_BROWN,
        COLOR_LIGHT_GRAY,
        COLOR_DARK_GRAY,
        COLOR_LIGHT_BLUE,
        COLOR_LIGHT_GREEN,
        COLOR_LIGHT_CYAN,
        COLOR_LIGHT_RED,
        COLOR_LIGHT_MAGENTA,
        COLOR_YELLOW,
        COLOR_WHITE,
    };

    std::array< std::pair<EColor, EColor>, 8 > colors;

    void attron( std::pair<EColor, EColor> colors ) {
        currAttrib = ((static_cast<int>(colors.second) << 4) | static_cast<int>(colors.first)) & 0xFF;
    }

    std::pair<EColor, EColor> COLOR_PAIR(int index ) {
        return colors[ index ];
    }

    void clear() {
        attron(COLOR_PAIR(4));

        for ( row = 0; row < 25; ++row ) {
            for ( col = 0; col < 80; ++col ) {
                _farpokeb(_dos_ds, 0xB800*16 + (( 80 * row * 2 ) + ( col * 2)), 0 );
                _farpokeb(_dos_ds, 0xB800*16 + (( 80 * row * 2 ) + ( col * 2)) + 1, currAttrib );
            }
        }

        col = row = 0;
    }

    void init_pair( int index, EColor attrib1, EColor attrib2) {
        colors[ index ] = std::make_pair(attrib1, attrib2);
    }

    void printw(std::string str ) {


        for ( const char& c : str ) {
            ++col;
           _farpokeb(_dos_ds, 0xB800*16 + (( 80 * row * 2 ) + ( col * 2)), c );
            _farpokeb(_dos_ds, 0xB800*16 + (( 80 * row * 2 ) + ( col * 2)) + 1, currAttrib );
        }
    }

    void addch(char ch) {
        ++col;
        _farpokeb(_dos_ds, 0xB800*16 + (( 80 * row * 2 ) + ( col * 2)), ch );
        _farpokeb(_dos_ds, 0xB800*16 + (( 80 * row * 2 ) + ( col * 2)) + 1, currAttrib );
    }

    void move( int y, int x ) {
        row = y;
        col = x;
    }

    void refresh() {
    }


    void endwin(){}

    void mvprintw( int y, int x, std::string str ) {
        move( y, x );
        printw( str );
    }


    CConsoleRenderer::CConsoleRenderer() {

        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_WHITE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_BLACK, COLOR_CYAN);

        printf("Dungeons Of Noudar\n");
        printf("Core edition.\n2017 - Daniel Monteiro\n\n\n");
        printf("%s\n", Knights::fileFromString("res/intro").c_str());
        printf("\nControls:\n+ and - cycle thru items in inventory\n");
        printf("i - turn left, o - move forward, p - turn right; q twice - quit\n");
        printf("tab - use item, [ - pick item, ] - drop item\nPress ENTER to start");

        getchar();
        clear();
    }

    CConsoleRenderer::~CConsoleRenderer() {
        endwin();
    }

    void CConsoleRenderer::drawMap(CMap &map, std::shared_ptr<CActor> current) {

        auto targetPosition = map.getTargetProjection(current);
		auto actorPosition = current->getPosition();



	    for (int cy = -10; cy < 10; ++cy ) {
            for (int cx = -10; cx < 10; ++cx) {
                move( cy + 10, cx + 10);
                auto x = actorPosition.x + cx;
                auto y = actorPosition.y + cy;
                auto actor = map.getActorAt( Vec2i{ x, y } );

                if (actor != nullptr) {
                    if (actor == current && current != nullptr) {
                        attron(COLOR_PAIR(1));
                        addch(directions[static_cast<int>(current->getDirection()) ]);
                    } else {
                        if ( current != nullptr && actor != nullptr && actor->getTeam() != current->getTeam() && actor->isAlive() ) {

	                        auto stance = actor->getStance();
                            if ( stance == EStance::kAttacking ) {
	                            attron(COLOR_PAIR(2));
                            } else if ( stance == EStance::kStanding ) {
	                            attron(COLOR_PAIR(6));
                            }

                        } else {
                            attron(COLOR_PAIR(5));
                        }
                        addch( actor->getView() );
                    }

                } else {

                    auto item = map.getItemAt({x, y});
                    if ( item != nullptr) {
                        attron(COLOR_PAIR(5));
                        addch(item->getView());
                        continue;
                    }

                    ItemView cellView = map.getItemViewAt( {x,y});

                    if ( cellView == kEmptySpace ) {
                        cellView = map.getElementAt( {x,y } );
                    }

                    if (map.isBlockProjectilesAt({x, y})) {
                        attron(COLOR_PAIR(7));
                        addch(cellView);
                    } else if (map.isBlockMovementAt({x, y})) {
                        attron(COLOR_PAIR(3));
                        addch(cellView);
                    } else {
                        if ( targetPosition.x == x && targetPosition.y == y ) {
                            attron(COLOR_PAIR(6));
                        } else {
                            attron(COLOR_PAIR(4));
                        }

                        addch(cellView);
                    }
                }

            }
        }
        attron(COLOR_PAIR(4));
        mvprintw( 21, 0, "-=-=-=-=-=-=-" );

        char buffer[ 80 ];

        if (current != nullptr) {
            std::fill( std::begin(buffer), std::end(buffer), ' ');
            mvprintw( 22,0, buffer );

            snprintf( buffer, 20, "Faith: %d", current->getHP() );

            mvprintw( 22,0, buffer );

            if ( current->getSelectedItem() != nullptr ) {
                std::fill( std::begin(buffer), std::end(buffer), ' ');
                mvprintw( 23, 0, buffer );
                mvprintw( 23, 0, current->getSelectedItem()->to_string().c_str());
            }

        }
        mvprintw( 24,0, "=-=-=-=-=-=-=" );

        refresh();
        ch = getch();
    }

    CommandType CConsoleRenderer::peekInput() {
        return ch;
    }

    CommandType CConsoleRenderer::getInput() {
        char toReturn = ch;
        ch = '.';
        return toReturn;
    }
}