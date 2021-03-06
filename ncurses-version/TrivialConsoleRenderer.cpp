/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/
#include <conio.h>
#include <stdio.h>
#include <bios.h>
#include <pc.h>
#include <unistd.h>
#include <termios.h>

#include <string>
#include <iostream>
#include <functional>
#include <memory>
#include <cstdlib>
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
#include "IRenderer.h"
#include "CConsoleRenderer.h"

namespace Knights {

    static const char directions[4] = { '^', '>', 'V', '<'};
    char ch = 0;

    CConsoleRenderer::CConsoleRenderer() {
        std::cout << std::endl;
        std::cout << "\x1B[2J\x1B[H" << std::endl;

        std::cout << "Dungeons Of Noudar" << std::endl;
        std::cout << "Core edition.\n2017 - Daniel Monteiro\n\n" << std::endl;
        std::cout << Knights::fileFromString("res/intro") << std::endl;
        std::cout << "\nControls:\n+ and - cycle thru items in inventory\n";
        std::cout << "i - turn left, o - move forward, p - turn right\n";
        std::cout << "tab - use item, [ - pick item, ] - drop item\nPress ENTER to start" << std::endl;
        getchar();
    }

    CConsoleRenderer::~CConsoleRenderer() {
    }

    void CConsoleRenderer::drawMap(CMap &map, std::shared_ptr<CActor> current) {

        auto targetPosition = map.getTargetProjection(current);
		auto actorPosition = current->getPosition();

	    std::cout << std::endl;
        std::cout << "\x1B[2J\x1B[H" << std::endl;
	    for (int y = std::max<int>(0, actorPosition.y - 10); y < std::min<int>( Knights::kMapSize, actorPosition.y + 10); ++y) {
            for (int x = std::max<int>(0, actorPosition.x - 10); x < std::min<int>( Knights::kMapSize, actorPosition.x + 10); ++x) {
                auto actor = map.getActorAt( Vec2i{ x, y } );

                std::cout << "\033[7;30m\033[0;32m";
                std::cout.flush();

                if (actor != nullptr) {
                    if (actor == current && current != nullptr) {
                        std::cout << "\033[33m";
                        std::cout << (directions[static_cast<int>(current->getDirection()) ]);
                    } else {

                        auto stance = actor->getStance();
                        if ( stance == EStance::kAttacking ) {
                            std::cout << "\033[31m";
                        } else if ( stance == EStance::kStanding ) {
                            std::cout << "\033[35m";
                        }


                        if ( !map.getActorAt( {x, y} )->isAlive() ) {
                            std::cout << "\033[37m";
                        }

                        std::cout << actor->getView();
                    }

                } else {

                    if (map.isBlockProjectilesAt({x, y})) {
                        std::cout << "\033[7;36m\033[30m";
                    } else if (map.isBlockMovementAt({x, y})) {
                        std::cout << "\033[36m";
                    } else {
                        if ( targetPosition == Knights::Vec2i{ x, y} ) {
                            std::cout << "\033[35m";
                        } else {
                            std::cout << "\033[32m";
                        }
                    }

                    auto cellView = map.getItemViewAt( {x,y} );
                    if ( cellView == kEmptySpace ) {
                        std::cout << (map.getElementAt( {x, y} ));
                    } else {
                        std::cout << cellView;
                    }
                }
            }
		    std::cout << std::endl;
        }
        std::cout << "\033[0m\033[32m";

        std::cout << "-=-=-=-=-=-=-" << std::endl;

        if (current != nullptr) {

            std::cout << "Faith: " << current->getHP() << std::endl;

            if (current->getSelectedItem() != nullptr ) {
                std::cout << current->getSelectedItem()->to_string() << std::endl;
            }
        }
        std::cout << "=-=-=-=-=-=-=" << std::endl;

        setvbuf(stdin, 0, _IONBF, 0);
        ch = getc(stdin);
    }

    CommandType CConsoleRenderer::getInput() {
		return ch;
    }
}
