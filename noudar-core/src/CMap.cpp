#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CDoorway.h"
#include "CTeam.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "CCharacterArchetype.h"
#include "CCharacter.h"

#include "CMonster.h"
#include "CElixirFountain.h"
#include "CDoorway.h"

#include <iostream>

namespace Knights {

    void CMap::endOfTurn() {
        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {
                if (mActors[y][x] != nullptr) {
                    mActors[y][x]->endOfTurn();
                }
            }
        }

        actors.erase(std::remove_if(actors.begin(), actors.end(),
                                    [](std::shared_ptr<CActor> actor) { return !actor->isAlive(); }
        ), actors.end());
    }

    CMap::CMap(const std::string &mapData, std::shared_ptr<CGameDelegate> aGameDelegate)
            : mGameDelegate(aGameDelegate) {

        char element;
        std::shared_ptr<CActor> actor = nullptr;

	    auto heroArchetype = std::make_shared<CCharacterArchetype>( 5, 2, 20, 7, '^', "Hero");
	    auto monsterArchetype = std::make_shared<CCharacterArchetype>( 4, 1, 5, 3, '@', "Monster");
	    auto friends = std::make_shared<CTeam>("Heroes");
	    auto foes = std::make_shared<CTeam>("Enemies");
        int id = 1;
        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {

                element = mapData[(y * kMapSize) + x];
                block[y][x] = false;
                map[y][x] = nullptr;
                mElement[y][x] = element;

                switch (element) {
                    case '0':
                    case '=':
                    case '_':
                    case '-':
                    case '(':
                    case ')':
                    case '2':
                    case '{':
                    case '}':
                    case '7':
                    case '!':
                    case 'H':
                        block[y][x] = false;
                        break;
                    case '1':
                    case '#':
                    case '/':
                    case '\\':
                    case '%':
                    case 'X':
                    case '|':
                    case 'Y':
                    case 'Z':
                    case 'S':
                    case '>':
                    case '<':
                    case '\'':
                        block[y][x] = true;
                        break;
                    case '~':
                        block[y][x] = false;
                        break;
	                case 'J':
		                actor = std::make_shared<CElixirFountain>(id++);
		                mElement[ y ][ x ] = '.';
		                break;
                    case '4':
                        actor = mAvatar = std::make_shared<CCharacter>( heroArchetype, friends, id++);
                        mElement[ y ][ x ] = '.';
                        break;
                    case '9':
                    case '*':
                        map[y][x] = std::make_shared<CDoorway>(
                                element == '9' ? EDoorwayFunction::kExit
                                               : EDoorwayFunction::kEntry);
                        break;
                    case '6':
                    case '5':
                        actor = std::make_shared<CMonster>( monsterArchetype, foes, id++);
                        mElement[ y ][ x ] = '.';
                        break;
                }

                if (actor != nullptr) {
                    actors.push_back(actor);
                    mActors[y][x] = actor;
                    actor->setPosition({x, y});
                    actor = nullptr;
                }
            }
        }
    }


    std::shared_ptr<CActor> CMap::attack(std::shared_ptr<CActor> actor, Vec2i position,
                                         bool mutual) {

        std::shared_ptr<CActor> otherActor = getActorAt(position);

        if (otherActor == nullptr) {
            return nullptr;
        }

        if (actor->getTeam() != otherActor->getTeam()) {

            actor->performAttack(otherActor);

            if (actor == mAvatar) {
                mGameDelegate->onPlayerAttacked(actor->getPosition());
                mGameDelegate->onMonsterDamaged(otherActor->getPosition());
            } else {
                mGameDelegate->onMonsterAttacked(actor->getPosition());
                mGameDelegate->onPlayerDamaged(otherActor->getPosition());
            }

            if (mutual) {
                otherActor->performAttack(actor);

                if (otherActor == mAvatar) {
                    mGameDelegate->onPlayerAttacked(otherActor->getPosition());
                    mGameDelegate->onMonsterDamaged(otherActor->getPosition());
                } else {
                    mGameDelegate->onMonsterAttacked(otherActor->getPosition());
                    mGameDelegate->onPlayerDamaged(otherActor->getPosition());
                }
            }

            if (!actor->isAlive()) {
                auto position = actor->getPosition();
                mActors[position.y][position.x] = nullptr;

                if (actor == mAvatar) {
                    mGameDelegate->onPlayerDied(actor->getPosition());
                } else {
                    mGameDelegate->onMonsterDied(actor->getPosition());
                }
            }

            if (!otherActor->isAlive()) {
                auto position = otherActor->getPosition();
                mActors[position.y][position.x] = nullptr;

                if (otherActor == mAvatar) {
                    mGameDelegate->onPlayerDied(otherActor->getPosition());
                } else {
                    mGameDelegate->onMonsterDied(otherActor->getPosition());
                }
            }
        }

        return otherActor;
    }

    Vec2i CMap::getActorTargetPosition(std::shared_ptr<CActor> actor) {

        auto position = actor->getPosition();

        switch (actor->getDirection()) {

            case EDirection::kEast:
                return Vec2i{position.x + 1, position.y};

            case EDirection::kWest:
                return Vec2i{position.x - 1, position.y};

            case EDirection::kSouth:
                return Vec2i{position.x, position.y + 1};

            default:
            case EDirection::kNorth:
                return Vec2i{position.x, position.y - 1};
        }
    }

    bool CMap::attackIfNotFriendly(EDirection d, std::shared_ptr<CActor> actor, bool mutual) {

        std::shared_ptr<CActor> other = nullptr;

        auto position = actor->getPosition();

        switch (d) {

            case EDirection::kEast:
                other = attack(actor, Vec2i{position.x + 1, position.y}, mutual);
                break;

            case EDirection::kWest:
                other = attack(actor, Vec2i{position.x - 1, position.y}, mutual);
                break;

            case EDirection::kSouth:
                other = attack(actor, Vec2i{position.x, position.y + 1}, mutual);
                break;

            case EDirection::kNorth:
                other = attack(actor, Vec2i{position.x, position.y - 1}, mutual);
                break;
        }

        return (other != nullptr);
    }


    void CMap::move(EDirection d, std::shared_ptr<CActor> actor) {

        if (actor->canAttack() && attackIfNotFriendly(d, actor, true)) {
            return;
        }

        if (!actor->canMove()) {
            return;
        }


        bool moved = false;

        auto position = actor->getPosition();

        switch (d) {

            case EDirection::kEast:

                if (!isBlockAt(position.x + 1, position.y)) {
                    moved = true;
                    moveActor(position, {position.x + 1, position.y}, actor);
                }
                break;

            case EDirection::kWest:
                if (!isBlockAt(position.x - 1, position.y)) {
                    moved = true;
                    moveActor(position, {position.x - 1, position.y}, actor);
                }
                break;

            case EDirection::kSouth:
                if (!isBlockAt(position.x, position.y + 1)) {
                    moved = true;
                    moveActor(position, {position.x, position.y + 1}, actor);
                }
                break;

            case EDirection::kNorth:
                if (!isBlockAt(position.x, position.y - 1)) {
                    moved = true;
                    moveActor(position, {position.x, position.y - 1}, actor);
                }
                break;

        }

        if (moved) {
            actor->onMove();
        }
    }

    bool CMap::isValid(int x, int y) {
        if (x < 0 || x >= kMapSize || y < 0 || y >= kMapSize) {
            return false;
        }
        return true;
    }

    bool CMap::isBlockAt(int x, int y) {

        if (!isValid(x, y)) {
            return true;
        }

        if (mActors[y][x] != nullptr) {
            return true;
        }

        return block[y][x];
    }

    std::shared_ptr<CActor> CMap::getActorAt(Vec2i position) {
        return mActors[position.y][position.x];
    }

    char CMap::getElementAt(int x, int y) {
        return mElement[y][x];
    }

    std::vector<std::shared_ptr<CActor>> CMap::getActors() {
        return actors;
    }

    std::shared_ptr<CActor> CMap::getAvatar() {
        return mAvatar;
    }

    void CMap::setActorAt(Vec2i position, std::shared_ptr<CActor> actor) {
        mActors[position.y][position.x] = actor;
    }

    bool CMap::isLevelFinished() {

        auto position = this->getAvatar()->getPosition();
        auto mapElement = (map[position.y][position.x]);

        if (mapElement != nullptr &&
            (mapElement->getView() == 'E' || mapElement->getView() == 'B')) {
            return (static_cast<Knights::CDoorway *>(&(*mapElement))->getDoorFunction() ==
                    EDoorwayFunction::kExit);
        }

        return false;
    }

    void CMap::moveActor(Vec2i from, Vec2i to, std::shared_ptr<CActor> actor) {
        mActors[from.y][from.x] = nullptr;
        mActors[to.y][to.x] = actor;
        actor->setPosition(to);
    }
}
