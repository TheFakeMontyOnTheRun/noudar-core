/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/

#include <string>
#include <functional>
#include <map>
#include <memory>
#include <ncurses.h>
#include <cstdlib>
#include <cstring>
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

    static const char directions[4] = { '^', '>', 'V', '<'};

    CConsoleRenderer::CConsoleRenderer() {
        initscr();
        clear();
        start_color();
        keypad (stdscr, TRUE);
        noecho();
        cbreak();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_WHITE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_BLACK, COLOR_CYAN);

        printw( "Dungeons Of Noudar\n");
        printw( "Core edition.\n2017 - Daniel Monteiro\n\n");
        printw( fileFromString("res/intro").c_str());
        printw( "\n\n\nPress any key to start\n");
    }

    CConsoleRenderer::~CConsoleRenderer() {
        endwin();
    }

    void CConsoleRenderer::drawMap(CMap &map, std::shared_ptr<CActor> current) {

        auto targetPosition = map.getTargetProjection(current);
		auto actorPosition = current->getPosition();

	    for (int y = 0; y < Knights::kMapSize; ++y ) {
		    for (int x = 0; x < Knights::kMapSize; ++x) {
			    move(y, x);
			    attron(COLOR_PAIR(3));
			    addch('.');
		    }
	    }


	    for (int y = std::max<int>(0, actorPosition.y - 10); y < std::min<int>( Knights::kMapSize, actorPosition.y + 10); ++y) {
            for (int x = std::max<int>(0, actorPosition.x - 10); x < std::min<int>( Knights::kMapSize, actorPosition.x + 10); ++x) {
                move( y - actorPosition.y + 10, x - actorPosition.x + 10);

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
        }

        attron(COLOR_PAIR(4));
        mvprintw( 22, 0, "-=-=-=-=-=-=-" );

        char buffer[ 20 ];

        if (current != nullptr) {
            std::fill( std::begin(buffer), std::end(buffer), 0);
            snprintf( buffer, 20, "Faith: %d", current->getHP() );

            mvprintw( 23,0, buffer );

            if ( current->getSelectedItem() != nullptr ) {
                mvprintw(24, 0, current->getSelectedItem()->to_string().c_str());
            }

        }
        mvprintw( 25,0, "=-=-=-=-=-=-=" );
        mvprintw( 26,0, "." );

        refresh();
    }

  Knights::CommandType CConsoleRenderer::peekInput() {
    return Knights::kNullCommand;
  }
  
    CommandType CConsoleRenderer::getInput() {
        int ch = getch();
        switch ( ch ) {
            case KEY_LEFT:
                return kTurnPlayerLeftCommand;
            case KEY_RIGHT:
                return kTurnPlayerRightCommand;
            case KEY_UP:
                return kMovePlayerForwardCommand;
            case KEY_DOWN:
                return kMovePlayerBackwardCommand;
            default:
                return ch;
        }
    }
}
