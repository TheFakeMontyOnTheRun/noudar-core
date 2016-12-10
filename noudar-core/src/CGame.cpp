#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
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

#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "CGame.h"

#include "commands/IGameCommand.h"
#include "commands/CMoveActorCommand.h"
#include "commands/CTurnActorCommand.h"
#include "commands/CActorMeleeAttackCommand.h"
#include "commands/CLoadNewLevelCommand.h"

const bool kShouldAlwaysFinishTurnOnMove = true;

namespace Knights {

    void CGame::endOfTurn(std::shared_ptr <CMap> map) {

        map->endOfTurn();

        for (auto &actor : map->getActors()) {
            actor->update(map);
        }

        ++mTurn;
    }

    std::shared_ptr <CMap> CGame::getMap() {
        return mMap;
    }

    void CGame::tick() {

	    if ( !mMap->getAvatar()->isAlive() ) {
		    playLevel( 0 );
	    } else {

		    std::shared_ptr <IGameCommand> command;

		    auto entry = mRenderer->getInput();

		    if (entry == kQuitGameCommand) {
			    mIsPlaying = false;
		    }

		    if (entry == kEndTurnCommand) {
			    endOfTurn(mMap);
		    }

		    if (entry == kMovePlayerEastCommand) {
			    command = std::make_shared<CMoveActorCommand>(shared_from_this(), EDirection::kEast, mMap->getAvatar());
		    }

		    if (entry == kActorMeleeAttackCommand) {

			    auto actor = mMap->getAvatar();
			    auto pos = mMap->getActorTargetPosition(actor);
			    auto otherActor = mMap->getActorAt(pos);

			    if (otherActor != nullptr && actor->getTeam() != otherActor->getTeam()) {
				    command = std::make_shared<CActorMeleeAttackCommand>(shared_from_this(), actor, otherActor);
			    }
		    }


		    if (entry == kMovePlayerNorthCommand) {
			    command = std::make_shared<CMoveActorCommand>(shared_from_this(), EDirection::kNorth,
			                                                  mMap->getAvatar());
		    }

		    if (entry == kMovePlayerWestCommand) {
			    command = std::make_shared<CMoveActorCommand>(shared_from_this(), EDirection::kWest, mMap->getAvatar());
		    }

		    if (entry == kMovePlayerSouthCommand) {
			    command = std::make_shared<CMoveActorCommand>(shared_from_this(), EDirection::kSouth,
			                                                  mMap->getAvatar());
		    }

		    if (entry == kTurnPlayerLeftCommand) {
			    std::shared_ptr <CActor> avatar = mMap->getAvatar();
			    command = std::make_shared<CTurnActorCommand>(shared_from_this(),
			                                                  wrapDirection(mMap->getAvatar()->getDirection(), -1),
			                                                  mMap->getAvatar());
		    }

		    if (entry == kMovePlayerForwardCommand) {
			    std::shared_ptr <CActor> avatar = mMap->getAvatar();
			    command = std::make_shared<CMoveActorCommand>(shared_from_this(), avatar->getDirection(), avatar);
		    }

		    if (entry == kTurnPlayerRightCommand) {
			    std::shared_ptr <CActor> avatar = mMap->getAvatar();
			    command = std::make_shared<CTurnActorCommand>(shared_from_this(),
			                                                  wrapDirection(mMap->getAvatar()->getDirection(), +1),
			                                                  mMap->getAvatar());
		    }

		    if (entry == kTurnPlayerNorthCommand) {
			    command = std::make_shared<CTurnActorCommand>(shared_from_this(), EDirection::kNorth,
			                                                  mMap->getAvatar());
		    }

		    if (entry == kTurnPlayerEastCommand) {
			    command = std::make_shared<CTurnActorCommand>(shared_from_this(), EDirection::kEast, mMap->getAvatar());
		    }

		    if (entry == kTurnPlayerSouthCommand) {
			    std::shared_ptr <CActor> avatar = mMap->getAvatar();

			    command = std::make_shared<CTurnActorCommand>(shared_from_this(), EDirection::kSouth,
			                                                  mMap->getAvatar());
		    }

		    if (entry == kTurnPlayerWestCommand) {
			    command = std::make_shared<CTurnActorCommand>(shared_from_this(), EDirection::kWest, mMap->getAvatar());
		    }

		    if (entry == kGoToFirstLevelCommand) {
			    command = std::make_shared<CLoadNewLevelCommand>(shared_from_this(), 1);
		    }

		    if (entry == kGoToTitleLevelCommand) {
			    command = std::make_shared<CLoadNewLevelCommand>(shared_from_this(), 0);
		    }


		    if (entry == kCastMagickForwardCommand) {
//            std::shared_ptr <CActor> avatar = mMap->getAvatar();
//
//                    int x;
//                    int y;
//
//                    std::cout << "target x?" << std::endl;
//                    std::cin >> x;
//                    std::cout << "target y?" << std::endl;
//                    std::cin >> y;
//
//                    map->attack(avatar, Vec2i{ x, y }, false);
//            if (kShouldAlwaysFinishTurnOnMove) {
//                endOfTurn(mMap);
//            }
		    }


		    if (command != nullptr) {
			    command->execute();

			    if (command->shouldEndTurn()) {
				    endOfTurn(mMap);
			    }
		    }
	    }

        {
            std::shared_ptr <CActor> avatar = mMap->getAvatar();
            mRenderer->drawMap(*mMap, avatar);
        }

    }

    CGame::CGame(std::shared_ptr<IFileLoaderDelegate> fileLoaderDelegate, std::shared_ptr <IRenderer> aRenderer,
                 std::shared_ptr <CGameDelegate> aGameDelegate) :
            mRenderer(aRenderer), mGameDelegate(aGameDelegate), mFileLoaderDelegate(fileLoaderDelegate) {
        mIsPlaying = true;
		playLevel( 0 );
    }

    bool CGame::isPlaying() {
        return mIsPlaying;
    }

    int CGame::getTurn() {
        return mTurn;
    }

	Vec2i CGame::getCursorPosition() {
		return mMap->getActorTargetPosition( mMap->getAvatar() );
	}

	void CGame::playLevel( int levelNumber ){
		std::stringstream ss;
		ss << mFileLoaderDelegate->getFilePathPrefix();
		ss << "map_tiles";
		ss << levelNumber;
		ss << ".txt";

		mLevel = levelNumber;
		mTurn = 0;
		auto mapData = mFileLoaderDelegate->loadFileFromPath( ss.str() );
		mMap = std::make_shared<CMap>(mapData, mGameDelegate);
	}

	void CGame::proceedToNextLevel() {
		playLevel( mLevel + 1);
	}
}