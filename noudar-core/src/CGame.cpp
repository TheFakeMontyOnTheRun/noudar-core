#include <functional>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <array>

using std::vector;
using std::array;

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
#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CMoveActorCommand.h"
#include "commands/CTurnActorCommand.h"
#include "commands/CLoadNewLevelCommand.h"
#include "commands/CCycleNextItemCommand.h"
#include "commands/CCyclePreviousItemCommand.h"
#include "commands/CUseCurrentItemCommand.h"
#include "commands/CPickItemCommand.h"
#include "commands/CDropItemCommand.h"
#include "commands/CSuggestItemCommand.h"

namespace Knights {

    void CGame::endOfTurn(std::shared_ptr<CMap> map) {

        map->endOfTurn(++mTurn);

        if (map->isLevelFinished()) {
            proceedToNextLevel();
            return;
        }


    }

    std::shared_ptr<CMap> CGame::getMap() {
        return mMap;
    }

    void CGame::tick() {

        if (!(mMap == nullptr || mMap->getAvatar() == nullptr || !mMap->getAvatar()->isAlive())) {

            std::shared_ptr<IGameCommand> command;

            auto entry = mRenderer->getInput();

            if (entry == kQuitGameCommand) {
                mIsPlaying = false;
            }

            if (entry == kEndTurnCommand) {
                endOfTurn(mMap);
            }

            if (entry == kMovePlayerEastCommand) {
                command = std::make_shared<CMoveActorCommand>(shared_from_this(), EDirection::kEast,
                                                              mMap->getAvatar());
            }

            if (entry == kMovePlayerNorthCommand) {
                command = std::make_shared<CMoveActorCommand>(shared_from_this(),
                                                              EDirection::kNorth,
                                                              mMap->getAvatar());
            }

            if (entry == kMovePlayerWestCommand) {
                command = std::make_shared<CMoveActorCommand>(shared_from_this(), EDirection::kWest,
                                                              mMap->getAvatar());
            }

            if (entry == kMovePlayerSouthCommand) {
                command = std::make_shared<CMoveActorCommand>(shared_from_this(),
                                                              EDirection::kSouth,
                                                              mMap->getAvatar());
            }

            if (entry == kTurnPlayerLeftCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CTurnActorCommand>(shared_from_this(),
                                                              wrapDirection(
                                                                      mMap->getAvatar()->getDirection(),
                                                                      -1),
                                                              mMap->getAvatar());
            }

            if (entry == kMovePlayerForwardCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CMoveActorCommand>(shared_from_this(),
                                                              avatar->getDirection(), avatar);
            }

            if (entry == kMovePlayerBackwardCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CMoveActorCommand>(shared_from_this(),
                                                              oppositeOf(avatar->getDirection()), avatar);
            }


            if (entry == kStrafeLeftCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CMoveActorCommand>(shared_from_this(),
                                                              leftOf(avatar->getDirection()), avatar);
            }

            if (entry == kStrafeRightCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CMoveActorCommand>(shared_from_this(),
                                                              rightOf(avatar->getDirection()), avatar);
            }


            if (entry == kTurnPlayerRightCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CTurnActorCommand>(shared_from_this(),
                                                              wrapDirection(
                                                                      mMap->getAvatar()->getDirection(),
                                                                      +1),
                                                              mMap->getAvatar());
            }

            if (entry == kTurnPlayerNorthCommand) {
                command = std::make_shared<CTurnActorCommand>(shared_from_this(),
                                                              EDirection::kNorth,
                                                              mMap->getAvatar());
            }

            if (entry == kTurnPlayerEastCommand) {
                command = std::make_shared<CTurnActorCommand>(shared_from_this(), EDirection::kEast,
                                                              mMap->getAvatar());
            }

            if (entry == kTurnPlayerSouthCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();

                command = std::make_shared<CTurnActorCommand>(shared_from_this(),
                                                              EDirection::kSouth,
                                                              mMap->getAvatar());
            }

            if (entry == kTurnPlayerWestCommand) {
                command = std::make_shared<CTurnActorCommand>(shared_from_this(), EDirection::kWest,
                                                              mMap->getAvatar());
            }

            if (entry == kGoToFirstLevelCommand) {
                command = std::make_shared<CLoadNewLevelCommand>(shared_from_this(), 1);
            }

            if (entry == kGoToTitleLevelCommand) {
                command = std::make_shared<CLoadNewLevelCommand>(shared_from_this(), 0);
            }

            if (entry == kCycleLeftInventoryCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CCyclePreviousItemCommand>(shared_from_this(), avatar);
            }

            if (entry == kCycleRightInventoryCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CCycleNextItemCommand>(shared_from_this(), avatar);
            }

            if (entry == kUseCurrentItemInInventoryCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CUseCurrentItemCommand>(shared_from_this(), avatar);
            }

            if (entry == kPickItemCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CPickItemCommand>(shared_from_this(), avatar);
            }

            if (entry == kDropItemCommand) {
                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CDropItemCommand>(shared_from_this(), avatar);
            }

            if (entry == '1' || entry == '2' || entry == '3') {
                ElementView itemView = '.';

                switch (entry) {
                    case '1':
                        itemView = 't';
                        break;
                    case '2':
                        itemView = 'y';
                        break;
                    case '3':
                        itemView = 'v';
                        break;
                }

                std::shared_ptr<CActor> avatar = mMap->getAvatar();
                command = std::make_shared<CSuggestItemCommand>(shared_from_this(), avatar, itemView);
            }

            if (command != nullptr) {
                command->execute();
                mLastCommand = command->to_string();

                if (command->shouldEndTurn()) {
                    endOfTurn(mMap);
                }
            }
        }

        {
            std::shared_ptr<CActor> avatar = mMap->getAvatar();
            mRenderer->drawMap(*mMap, avatar);
        }

    }

    CGame::CGame(std::shared_ptr<IFileLoaderDelegate> fileLoaderDelegate,
                 std::shared_ptr<IRenderer> aRenderer,
                 std::shared_ptr<CGameDelegate> aGameDelegate) :
            mRenderer(aRenderer), mGameDelegate(aGameDelegate),
            mFileLoaderDelegate(fileLoaderDelegate) {
        mIsPlaying = true;
#ifndef DONT_LOAD_LEVEL_UPON_START
        playLevel(0);
#endif
    }

    bool CGame::isPlaying() {
        return mIsPlaying;
    }

    int CGame::getTurn() {
        return mTurn;
    }

    Vec2i CGame::getCursorPosition() {
        return mMap->getActorTargetPosition(mMap->getAvatar());
    }

    void CGame::playLevel(int levelNumber) {

        mGameDelegate->onLevelWillLoad();

        char buffer[10];
        snprintf(buffer, 9, "map%d.txt", levelNumber);

        mLevel = levelNumber;
        mTurn = 0;

        if (mMap != nullptr && mMap->getAvatar() != nullptr && mMap->getAvatar()->isAlive()) {
            mPlayerActor = mMap->getAvatar();
        }

        auto mapData = mFileLoaderDelegate->loadFileFromPath(buffer);
        mMap = std::make_shared<CMap>(mapData, mGameDelegate);

        if (mPlayerActor != nullptr && levelNumber != 0) {
            mMap->getAvatar()->copyStateFrom(mPlayerActor);
        }

        mGameDelegate->onLevelLoaded();
    }

    void CGame::proceedToNextLevel() {
        playLevel(mLevel + 1);
    }

    Knights::ActorId CGame::getCurrentActorId() {
        return mMap->getAvatar()->getId();
    }

    int CGame::getLevelNumber() {
        return mLevel;
    }

    void CGame::setIsPlaying(bool isPlaying) {
        mIsPlaying = isPlaying;
    }

    std::string CGame::getLastCommand() {
        return mLastCommand;
    }
}
