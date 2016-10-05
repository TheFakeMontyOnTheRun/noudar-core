/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <ncurses.h>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CMap.h"
#include "IRenderer.h"
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
    }

    CConsoleRenderer::~CConsoleRenderer() {
        endwin();
    }

    void CConsoleRenderer::drawMap(const CMap &map, std::shared_ptr<CActor> current) {

        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                move( y, x );

                if (map.map[y][x] != nullptr) {
                    if (map.map[y][x] == current && current != nullptr) {
                        attron(COLOR_PAIR(1));
                    } else {

                        auto otherActor = std::dynamic_pointer_cast<CActor>(map.map[y][x]);

                        if ( current != nullptr && otherActor != nullptr && otherActor->mTeam == current->mTeam ) {
                            attron(COLOR_PAIR(5));
                        } else {
                            attron(COLOR_PAIR(2));
                        }
                    }
                    addch(map.map[y][x]->mView);
                } else {
                    if (map.block[y][x]) {
                        attron(COLOR_PAIR(3));
                        addch('#');
                    } else {
                        attron(COLOR_PAIR(4));
                        addch('.');
                    }
                }

            }
        }

        attron(COLOR_PAIR(4));
        mvprintw( 22, 0, "-=-=-=-=-=-=-" );

        char buffer[ 7 ];

        if (current != nullptr) {

            snprintf( buffer, 6, "HP: %d", current->mHP );
            mvprintw( 23,0, buffer );

            snprintf( buffer, 6, "AT: %d", current->mAttack );
            mvprintw( 24,0, buffer );

            snprintf( buffer, 6, "DF: %d", current->mDefence );
            mvprintw( 25,0, buffer );

            snprintf( buffer, 6, "AP: %d", current->mRemainingAP );
            mvprintw( 26,0, buffer );

            snprintf( buffer, 6, "HD: %c", directions[static_cast<int>(current->mDirection) ] );
            mvprintw( 27,0, buffer );

        }
        mvprintw( 28,0, "-//-" );

        refresh();
    }

    char CConsoleRenderer::getInput() {
        int ch = getch();
        switch ( ch ) {
            case KEY_LEFT:
                return 'i';
            case KEY_RIGHT:
                return 'p';
            case KEY_UP:
                return 'o';
            default:
                return ch;
        }
    }
}