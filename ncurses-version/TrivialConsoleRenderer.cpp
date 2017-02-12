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
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CConsoleRenderer.h"
#include <conio.h>
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

	    std::cout << std::endl << std::endl;;

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
	                std::cout << (map.getElementAt( x, y));
                }
            }
		    std::cout << std::endl;
        }

        ch = getchar();
    }

    char CConsoleRenderer::getInput() {
		return ch;
    }
}