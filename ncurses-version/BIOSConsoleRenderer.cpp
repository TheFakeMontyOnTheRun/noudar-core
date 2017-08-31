/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/
#include <go32.h>
#include <sys/farptr.h>
#include <conio.h>
#include <dpmi.h>
#include <pc.h>
#include <bios.h>
#include <time.h>
#include <unistd.h>
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/movedata.h>
#include <pc.h>
#include <sys/farptr.h>
#include <bios.h>
#include <sys/nearptr.h>

#include <cstdlib>
#include <cstdio>
#include <functional>
#include <cmath>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <memory>
#include <iostream>
#include <map>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <map>
#include <memory>
#include <cstdlib>
#include <array>
#include <fstream>
#include <cstring>

using std::vector;
using std::array;

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

    static const char directions[4] = { '^', '>', 'V', '<'};
    char ch = 0;
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

    void clear() {
        clrscr();
    }

    void init_pair( int index, EColor attrib1, EColor attrib2) {
        colors[ index ] = std::make_pair(attrib1, attrib2);
    }

    void printw(std::string str ) {
        std::cout << str << std::endl;
    }

    void addch(char ch) {
        std::cout << ch;
    }

    void attron( std::pair<EColor, EColor> colors ) {
        textcolor(static_cast<int>(colors.first));
        textbackground(static_cast<int>(colors.second));
        textattr((BLUE << 4) | WHITE);

    }

    void move( int y, int x ) {
//        gotoxy(x, y);
    }

    std::pair<EColor, EColor> COLOR_PAIR(int index ) {
        return colors[ index ];
    }

    void refresh() {
        std::cout.flush();
    }

    void endwin(){}

    void mvprintw( int y, int x, std::string str ) {
        move( y, x );
        printw( str );
    }


    CConsoleRenderer::CConsoleRenderer() {

        textmode(C80);


        clear();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_WHITE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_BLACK, COLOR_CYAN);

        std::cout << "Dungeons Of Noudar" << std::endl;
        std::cout << "Core edition.\n2017 - Daniel Monteiro\n\n" << std::endl;
        std::cout << Knights::fileFromString("res/intro") << std::endl;
        std::cout << "\nControls:\n+ and - cycle thru items in inventory\n";
        std::cout << "i - turn left, o - move forward, p - turn right; q twice - quit\n";
        std::cout << "tab - use item, [ - pick item, ] - drop item\nPress ENTER to start" << std::endl;
        getchar();
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
            std::cout << std::endl;
        }
        std::cout << std::endl;
        attron(COLOR_PAIR(4));
        mvprintw( 21, 0, "-=-=-=-=-=-=-" );

        char buffer[ 20 ];

        if (current != nullptr) {
            std::fill( std::begin(buffer), std::end(buffer), 0);
            snprintf( buffer, 20, "Faith: %d", current->getHP() );

            mvprintw( 22,0, buffer );

            if ( current->getSelectedItem() != nullptr ) {
                mvprintw(23, 0, current->getSelectedItem()->to_string().c_str());
            }

        }
        mvprintw( 24,0, "=-=-=-=-=-=-=" );

//        setvbuf(stdin, 0, _IONBF, 0);
        refresh();
        ch = getch();
    }

    CommandType CConsoleRenderer::getInput() {
        char toReturn = ch;
        ch = '.';
        return toReturn;
    }
}