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
#include <cstdlib>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CConsoleRenderer.h"
#include <conio.h>
#include <stdio.h>
#include <bios.h>
#include <pc.h>
#include <unistd.h>
#include <termios.h>

namespace Knights {

    static const char directions[4] = { '^', '>', 'V', '<'};
    char ch = 0;

    CConsoleRenderer::CConsoleRenderer() {
    }

    CConsoleRenderer::~CConsoleRenderer() {
    }

    void CConsoleRenderer::drawMap(CMap &map, std::shared_ptr<CActor> current) {

        auto targetPosition = map.getActorTargetPosition(current);
		auto actorPosition = current->getPosition();

	    std::cout << std::endl;
        std::cout << "\x1B[2J\x1B[H" << std::endl;
	    for (int y = std::max<int>(0, actorPosition.y - 10); y < std::min<int>( Knights::kMapSize, actorPosition.y + 10); ++y) {
            for (int x = std::max<int>(0, actorPosition.x - 10); x < std::min<int>( Knights::kMapSize, actorPosition.x + 10); ++x) {

                auto actor = map.getActorAt( Vec2i{ x, y } );

                if (actor != nullptr) {
                    if (actor == current && current != nullptr) {
                        std::cout << (directions[static_cast<int>(current->getDirection()) ]);
                    } else {
                        std::cout << (directions[static_cast<int>(actor->getDirection()) ]);
                    }

                } else {
	                std::cout << (map.getElementAt( {x, y} ));
                }
            }
		    std::cout << std::endl;
        }

        std::cout << "-=-=-=-=-=-=-" << std::endl;

        if (current != nullptr) {

            std::cout << "HP: " << current->getHP() << std::endl;
            std::cout << "AT: " << current->getAttack() << std::endl;
            std::cout << "DF: " << current->getDefense() << std::endl;
            std::cout << "AP: " << current->getAP() << std::endl;

            if (current->getSelectedItem() != nullptr ) {
                std::cout << current->getSelectedItem()->to_string() << std::endl;
            }

            std::cout << current->getCurrentSay() << std::endl;
        }
        std::cout << "-//-" << std::endl;

        setvbuf(stdin, 0, _IONBF, 0);
        ch = getc(stdin);
    }

    char CConsoleRenderer::getInput() {
		return ch;
    }
}