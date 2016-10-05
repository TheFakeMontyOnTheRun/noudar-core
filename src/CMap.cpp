#include <string>
#include <vector>
#include <memory>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CDoorway.h"
#include "CActor.h"
#include "CMap.h"
#include "CBullKnight.h"
#include "CFalconKnight.h"
#include "CTurtleKnight.h"
#include "CCuco.h"

#include <iostream>
#include <typeinfo>

namespace Knights {
    void CMap::endOfTurn() {
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                if (std::dynamic_pointer_cast<CActor>(map[y][x]) != nullptr) {
                    std::dynamic_pointer_cast<CActor>(map[y][x])->endOfTurn();
                }
            }
        }
    }


    CMap::CMap(const std::string &mapData) {

        char element;
        std::shared_ptr<CActor> actor = nullptr;
        int id = 0;
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {

                element = mapData[(y * 20) + x];
                block[y][x] = false;
                map[y][x] = nullptr;

                switch (element) {
                    case '0':
                    case '1':
                        block[y][x] = (element == '1');
                        break;

                    case '4':
                        actor = bull = std::make_shared<CBullKnight>(id++);
                        break;
                    case '3':
                        actor = turtle = std::make_shared<CTurtleKnight>(id++);
                        break;
                    case '2':
                        actor = falcon = std::make_shared<CFalconKnight>(id++);
                        break;
                    case '9':
                    case '*':
                        map[y][x] = std::make_shared<CDoorway>(element == '9' ? EDoorwayFunction::kExit : EDoorwayFunction::kEntry);
                        break;
                    case '5':
                    case '6':
                        actor = std::make_shared<CCuco>(id++);
                        break;
                }

                if (actor != nullptr) {
                    actors.push_back(actor);
                    map[y][x] = actor;
                    actor->mPosition = { x, y };
                    actor = nullptr;
                }
            }
        }
    }


    std::shared_ptr<CActor> CMap::attack(std::shared_ptr<CActor> actor, Vec2i position, bool mutual) {

        auto other = map[ position.y][ position.x];

        std::shared_ptr<CActor> otherActor = std::dynamic_pointer_cast<CActor>( other );

        if ( otherActor == nullptr ) {
            return nullptr;
        }

        if (other != nullptr && actor->mTeam != otherActor->mTeam) {
            actor->performAttack(otherActor);

            if (mutual) {
                otherActor->performAttack(actor);
            }

            if (actor->mHP <= 0) {
                map[actor->mPosition.y][actor->mPosition.x] = nullptr;
            }

            if (otherActor->mHP <= 0) {
                map[other->mPosition.y][other->mPosition.x] = nullptr;
            }
        }

        return otherActor;
    }


    bool CMap::attackIfNotFriendly(EDirection d, std::shared_ptr<CActor> actor, bool mutual) {

        std::shared_ptr<CActor> other = nullptr;

        switch (d) {

            case EDirection::kEast:
                other = attack(actor, Vec2i{actor->mPosition.x + 1, actor->mPosition.y}, mutual);
                break;

            case EDirection::kWest:
                other = attack(actor, Vec2i{actor->mPosition.x - 1, actor->mPosition.y}, mutual);
                break;

            case EDirection::kSouth:
                other = attack(actor, Vec2i{actor->mPosition.x, actor->mPosition.y + 1}, mutual);
                break;

            case EDirection::kNorth:
                other = attack(actor, Vec2i{actor->mPosition.x, actor->mPosition.y - 1}, mutual);
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

        switch (d) {

            case EDirection::kEast:
                if (!block[actor->mPosition.y][actor->mPosition.x + 1]) {
                    moved = true;
                    map[actor->mPosition.y][actor->mPosition.x] = nullptr;
                    ++actor->mPosition.x;
                    map[actor->mPosition.y][actor->mPosition.x] = actor;
                }
                break;

            case EDirection::kWest:
                if (!block[actor->mPosition.y][actor->mPosition.x - 1]) {
                    moved = true;
                    map[actor->mPosition.y][actor->mPosition.x] = nullptr;
                    --actor->mPosition.x;
                    map[actor->mPosition.y][actor->mPosition.x] = actor;
                }
                break;

            case EDirection::kSouth:
                if (!block[actor->mPosition.y + 1][actor->mPosition.x]) {
                    moved = true;
                    map[actor->mPosition.y][actor->mPosition.x] = nullptr;
                    ++actor->mPosition.y;
                    map[actor->mPosition.y][actor->mPosition.x] = actor;
                }
                break;

            case EDirection::kNorth:
                if (!block[actor->mPosition.y - 1][actor->mPosition.x]) {
                    moved = true;
                    map[actor->mPosition.y][actor->mPosition.x] = nullptr;
                    --actor->mPosition.y;
                    map[actor->mPosition.y][actor->mPosition.x] = actor;
                }
                break;

        }

        if (moved) {
            actor->onMove();
        }
    }
}