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
#include "CBaphomet.h"
#include "CBullKnight.h"
#include "CCuco.h"
#include "CDemon.h"
#include "CFalconKnight.h"
#include "CMoura.h"
#include "CTurtleKnight.h"
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

        char entry = mRenderer->getInput();

        if ( entry == 'q') {
            mIsPlaying = false;
        }

        if (avatar != nullptr) {

            if (entry == 't') {
                endOfTurn(mMap);
            }

            if (entry == 's') {
                mMap->move( EDirection ::kEast, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }
            }

            if (entry == 'w') {
                mMap->move( EDirection::kNorth, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }

            }

            if (entry == 'a') {
                mMap->move( EDirection::kWest, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }

            }

            if (entry == 'z') {
                mMap->move( EDirection::kSouth, avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }

            }


            if (entry == 'i') {
                avatar->turnLeft();
            }

            if (entry == 'o') {
                mMap->move( avatar->getDirection(), avatar);

                if ( kShouldAlwaysFinishTurnOnMove ) {
                    endOfTurn( mMap );
                }
            }

            if (entry == 'p') {
                avatar->turnRight();
            }

            if ( entry == 'r' ) {
                avatar->setDirection( EDirection::kNorth );
            }

	        if ( entry == 'f' ) {
		        avatar->setDirection( EDirection::kEast );
	        }

	        if ( entry == 'c' ) {
		        avatar->setDirection( EDirection::kSouth );
	        }

	        if ( entry == 'd' ) {
		        avatar->setDirection( EDirection::kWest );
	        }

            if (entry == 'c') {

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