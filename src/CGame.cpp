#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CMap.h"
#include "CDoorway.h"
#include "CBaphomet.h"
#include "CBullKnight.h"
#include "CCuco.h"
#include "CDemon.h"
#include "CFalconKnight.h"
#include "CMoura.h"
#include "CTurtleKnight.h"
#include "IRenderer.h"
#include "CConsoleRenderer.h"
#include "CGame.h"

int turn = 1;
bool playing = true;
const bool kShouldAlwaysFinishTurnOnMove = true;

namespace Knights {

    void CGame::endOfTurn( std::shared_ptr<CMap> map ) {

        map->endOfTurn();
        ++turn;
    }

    CGame::CGame( std::string mapData, std::shared_ptr<IRenderer> renderer) {
        std::string entry;

        auto map = std::make_shared<CMap>(mapData);

        std::shared_ptr<CActor> avatar = map->falcon;

        while (playing) {

            renderer->drawMap(*map, avatar);

            if (avatar != nullptr && avatar->mHP <= 0) {
                avatar = nullptr;
            }

            entry = renderer->getInput();

            if ( entry == "q") {
                playing = false;
            }

            if (avatar != nullptr) {

                if (entry == "t") {
                    endOfTurn(map);
                }

                if (entry == "s") {
                    map->move( EDirection ::kEast, avatar);

                    if ( kShouldAlwaysFinishTurnOnMove ) {
                        endOfTurn( map );
                    }
                }

                if (entry == "w") {
                    map->move( EDirection::kNorth, avatar);

                    if ( kShouldAlwaysFinishTurnOnMove ) {
                        endOfTurn( map );
                    }

                }

                if (entry == "a") {
                    map->move( EDirection::kWest, avatar);

                    if ( kShouldAlwaysFinishTurnOnMove ) {
                        endOfTurn( map );
                    }

                }

                if (entry == "z") {
                    map->move( EDirection::kSouth, avatar);

                    if ( kShouldAlwaysFinishTurnOnMove ) {
                        endOfTurn( map );
                    }

                }


                if (entry == "i") {
                    avatar->turnLeft();
                }

                if (entry == "o") {
                    map->move( avatar->mDirection, avatar);

                    if ( kShouldAlwaysFinishTurnOnMove ) {
                        endOfTurn( map );
                    }
                }

                if (entry == "p") {
                    avatar->turnRight();
                }

                if (entry == "c") {

//                    int x;
//                    int y;
//
//                    std::cout << "target x?" << std::endl;
//                    std::cin >> x;
//                    std::cout << "target y?" << std::endl;
//                    std::cin >> y;
//
//                    map->attack(avatar, Vec2i{ x, y }, false);
                    if ( kShouldAlwaysFinishTurnOnMove ) {
                        endOfTurn( map );
                    }
                }
            }

            if (entry == "1") {
                avatar = map->falcon;
            }

            if (entry == "2") {
                avatar = map->turtle;
            }

            if (entry == "3") {
                avatar = map->bull;
            }

        }
    }
}