#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "CDoorway.h"
#include "CKnight.h"
#include "CCuco.h"
#include "IRenderer.h"

#include "CGame.h"

const bool kShouldAlwaysFinishTurnOnMove = true;

namespace Knights {

    void CGame::endOfTurn( std::shared_ptr<CMap> map ) {

        map->endOfTurn();

        for ( auto& actor : map->getActors() ) {
            actor->update( map );
        }

        ++mTurn;
    }

    void CGame::tick() {
        std::shared_ptr<CActor> avatar = mMap->getAvatar();

        if (avatar != nullptr && !avatar->isAlive()) {
            avatar = nullptr;
        }

        auto entry = mRenderer->getInput();

        if ( entry == kQuitGameCommand ) {
            mIsPlaying = false;
        }

        if (avatar != nullptr) {

            if (entry == kEndTurnCommand ) {
                endOfTurn(mMap);
            }

            if (entry == kMovePlayerEastCommand ) {
                mMap->move( EDirection ::kEast, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }
            }

            if (entry == kMovePlayerNorthCommand ) {
                mMap->move( EDirection::kNorth, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }

            }

            if (entry == kMovePlayerWestCommand ) {
                mMap->move( EDirection::kWest, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }

            }

            if (entry == kMovePlayerSouthCommand ) {
                mMap->move( EDirection::kSouth, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }

            }


            if (entry == kTurnPlayerLeftCommand) {
                avatar->turnLeft();
            }

            if (entry == kMovePlayerForwardCommand ) {
                mMap->move( avatar->getDirection(), avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }
            }

            if (entry == kTurnPlayerRightCommand ) {
                avatar->turnRight();
            }

            if ( entry == kTurnPlayerNorthCommand  ) {
                avatar->setDirection( EDirection::kNorth );
            }

	        if ( entry == kTurnPlayerEastCommand ) {
		        avatar->setDirection( EDirection::kEast );
	        }

	        if ( entry == kTurnPlayerSouthCommand ) {
		        avatar->setDirection( EDirection::kSouth );
	        }

	        if ( entry ==  kTurnPlayerWestCommand ) {
		        avatar->setDirection( EDirection::kWest );
	        }

            if (entry == kCastMagickForwardCommand ) {

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
                    endOfTurn( mMap );
                }
            }
        }

        mRenderer->drawMap(*mMap, avatar);

    }

    CGame::CGame( std::string mapData, std::shared_ptr<IRenderer> aRenderer, std::shared_ptr<CGameDelegate> aGameDelegate ) :
    mRenderer( aRenderer ), mGameDelegate( aGameDelegate ) {
        mMap = std::make_shared<CMap>(mapData, aGameDelegate);
        mIsPlaying = true;
    }

    bool CGame::isPlaying() {
        return mIsPlaying;
    }

    int CGame::getTurn() {
        return mTurn;
    }
}