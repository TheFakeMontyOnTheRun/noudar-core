#include <string>
#include <array>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CDoorway.h"
#include "CTeam.h"
#include "CItem.h"
#include "CStorageItem.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "CCharacterArchetype.h"
#include "CCharacter.h"

#include "CMonster.h"
#include "CDoorway.h"
#include "CItem.h"
#include <iostream>
#include <sstream>
#include "CMonsterGenerator.h"
#include "CRandomWorldGenerator.h"

namespace Knights {

    const auto kCrossbowAmmoUsage = 3;
    const auto kShieldPowerUsage = 5;
    const auto kImprovedDamageRatio = 9;

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
	    auto monsterArchetype = std::make_shared<CCharacterArchetype>( 4, 1, 10, 3, '@', "Monster");
	    auto friends = std::make_shared<CTeam>("Heroes");
	    auto foes = std::make_shared<CTeam>("Enemies");
        int pos = 0;
        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {

                element = mapData[ pos ];
                actor = nullptr;
                block[y][x] = false;
                map[y][x] = nullptr;
                mActors[ y ][ x ] = nullptr;
                mElement[y][x] = element;
				mItems[ y ][ x ] = nullptr;

                switch (element) {
	                default:
                    case '0':
                    case 'O':
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
	                case 't':
		                block[y][x] = false;
		                mElement[ y ][ x ] = '.';
		                mItems[ y ][ x ] = std::make_shared<CItem>("Sword of sorrow", 't', false, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){
                            auto target = aMap->getActorTargetPosition(aActor);
                            aMap->attack( aActor, target, true );
		                });
		                break;
                    case 'v':
                        block[y][x] = false;
                        mElement[ y ][ x ] = '.';
                        mItems[ y ][ x ] = std::make_shared<CStorageItem>("Shield of restoration", 'v', false, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){

                            auto shield = (CStorageItem*)aActor->getItemWithSymbol( 'v' ).get();

                            if ( shield  == nullptr ) {
                                return;
                            }

                            if ( shield->getAmount() > 0 ) {
                                aActor->addHP( 1 );
                                shield->add( -1 );
                            }

                        }, 0);
                        break;

                    case 'u':
                        block[y][x] = false;
                        mElement[ y ][ x ] = '.';
                        mItems[ y ][ x ] = std::make_shared<CStorageItem>("Quiver", 'u', false, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){}, 5);
                        break;
                    case '+':
                        block[y][x] = false;
                        mElement[ y ][ x ] = '.';
                        mItems[ y ][ x ] = std::make_shared<CItem>("The holy health", '+', true, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){
                            aActor->addHP(5);
                        });
                        break;

	                case 'y':
		                block[y][x] = false;
		                mElement[ y ][ x ] = '.';
                        //The need for RTTI creeps again...
		                mItems[ y ][ x ] = std::make_shared<CStorageItem>("Crossbow of damnation", 'y', false, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){

                            auto shield = (CStorageItem*)aActor->getItemWithSymbol( 'v' ).get();
                            auto crossbow = (CStorageItem*)aActor->getItemWithSymbol( 'y' ).get();

                            bool shieldHasAmmo = false;
                            bool crossbowHasAmmo = false;

                            if ( crossbow != nullptr ) {
                                crossbowHasAmmo = (crossbow->getAmount() >= kCrossbowAmmoUsage );
                            }

                            if ( shield != nullptr ) {
                                shieldHasAmmo = (shield->getAmount() >= kShieldPowerUsage );
                            }

                            if ( !crossbowHasAmmo ) {
                                return;
                            }

                            auto target = aMap->projectLineOfSight( aMap->getActorTargetPosition(aActor), aActor->getDirection() );

                            if ( !( target == aActor->getPosition() ) ) {
                                aMap->attack( aActor, target, false );

                                if ( shieldHasAmmo ) {
                                    for ( int ratio = kImprovedDamageRatio; ratio > 0; --ratio ) {
                                        aMap->attack( aActor, target, false );
                                    }
                                }
                            }

                            aMap->getGameDelegate()->onProjectileHit( target);

                            crossbow->add( - ( kCrossbowAmmoUsage ) );

                            if ( shieldHasAmmo ) {
                                shield->add( -( kShieldPowerUsage ) );
                            }

                        }, 0);
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

                    case '4':
                        actor = mAvatar = std::make_shared<CCharacter>( heroArchetype, friends, getLastestId(), [](std::shared_ptr<CActor> character, std::shared_ptr<CMap> map){
                            auto shield = (CStorageItem*)character->getItemWithSymbol( 'v' ).get();
                            if ( shield != nullptr && map->getElementAt( character->getPosition() ) == '*' ) {
                                if ( shield->getAmount() < 20 ) {
                                    shield->add( 1 );
                                }
                            }

                            auto crossbow = (CStorageItem*)character->getItemWithSymbol( 'y' ).get();

                            if ( crossbow  == nullptr ) {
                                return;
                            }

                            if ( crossbow->getAmount() < 20 ) {
                                crossbow->add( 1 );
                            }

                        });
                        mElement[ y ][ x ] = '.';
                        break;

                    case '9':
                        {
                            map[y][x] = std::make_shared<CDoorway>();
                            mElement[y][x] = map[y][x]->getView();
                        }
                        break;

                    case 'T':
                    {
                        auto ropeArchetype = std::make_shared<CCharacterArchetype>( 0, 0, 10000, 0, 'T', "Rope");

                        actor = std::make_shared<CCharacter>( ropeArchetype, foes, getLastestId(), [](std::shared_ptr<CActor> character, std::shared_ptr<CMap> map){
                            auto archetype = ((CCharacter*)character.get())->getArchetype();

                            if ( archetype.getHP() > character->getHP() ) {
                                map->floodFill( character->getPosition(), '#', '~' );
                                character->addHP( -character->getHP() );
                            }

                        });


                        mElement[ y ][ x ] = '#';
                    }
                    break;
                    case 'J':
                    case '6':
                    case '5':
                        actor = std::make_shared<CMonster>( monsterArchetype, foes, getLastestId());
                        mElement[ y ][ x ] = '.';
                        break;
                    case 'G':
                        actor = std::make_shared<CMonsterGenerator>(getLastestId(), 5);
                        mElement[ y ][ x ] = '.';
                        break;

                }

                if (actor != nullptr) {
                    actors.push_back(actor);
                    mActors[y][x] = actor;
                    actor->setPosition({x, y});
                    actor = nullptr;
                }

                ++pos;
            }
            //skip \n
            ++pos;
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
        return actor->getPosition() + mapOffsetForDirection( actor->getDirection() );
    }

    void CMap::move(EDirection d, std::shared_ptr<CActor> actor) {

        if (!actor->canMove()) {
            return;
        }

        auto position = actor->getPosition();
        auto offset = mapOffsetForDirection( d );
        auto newPosition = position + offset;

        if (!isBlockAt(newPosition)) {
            moveActor(position, newPosition, actor);
            actor->onMove();
        }
    }

    bool CMap::isValid(const Vec2i& p) {
        if (p.x < 0 || p.x >= kMapSize || p.y < 0 || p.y >= kMapSize) {
            return false;
        }
        return true;
    }

    bool CMap::isBlockAt(const Vec2i& p) {

        if (!isValid(p)) {
            return true;
        }

        if (mActors[p.y][p.x] != nullptr) {
            return true;
        }

        return block[p.y][p.x];
    }

    std::shared_ptr<CActor> CMap::getActorAt(Vec2i position) {
	    if ( isValid( position ) ) {
		    return mActors[position.y][position.x];
	    } else {
		    return nullptr;
	    }
    }

    char CMap::getElementAt(const Vec2i& p) {

	    if ( mItems[ p.y ][ p.x ] != nullptr ) {
		    return mItems[ p.y ][ p.x ]->getView();
	    }

        return mElement[p.y][p.x];
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
        return mElement[position.y][position.x] == 'E';
    }

    void CMap::moveActor(Vec2i from, Vec2i to, std::shared_ptr<CActor> actor) {
        mActors[from.y][from.x] = nullptr;
        mActors[to.y][to.x] = actor;
        actor->setPosition(to);
    }

	Vec2i CMap::projectLineOfSight(Vec2i aPosition, EDirection aDirection) {

		auto offset = mapOffsetForDirection( aDirection );
		auto position = aPosition;
		std::shared_ptr<CActor> toReturn = nullptr;

        auto previous = position;
		while ( isValid( position ) && !isBlockAt( position ) ) {

            previous = position;

            position += offset;

			auto actor = getActorAt( position );

            if ( actor != nullptr ) {
                return actor->getPosition();
            }
		}

        return previous;
	}

	void CMap::giveItemAt(Vec2i from, std::shared_ptr<CActor> actor) {

        if ( !isValid( from )) {
            return;
        }

        if ( mItems[ from.y ][ from.x ] != nullptr ) {
            auto item = mItems[ from.y ][ from.x ];
	        mItems[ from.y ][ from.x ] = nullptr;
	        actor->giveItem( item );
        }
	}

    std::shared_ptr<Knights::CItem> CMap::getItemAt( Vec2i from ) {

        if ( !isValid( from ) ) {
            return nullptr;
        }

        return mItems[ from.y ][ from.x ];
    }

	void CMap::putItemAt(std::shared_ptr<CItem> aItem, Vec2i aDestination) {
		if ( mItems[ aDestination.y ][ aDestination.x ] == nullptr ) {
			mItems[ aDestination.y ][ aDestination.x ] = aItem;
		}
	}

    void CMap::addActorAt(std::shared_ptr<CActor> actor, const Vec2i &position) {
        mElement[ position.y ][ position.x ] = '.';
        actors.push_back(actor);
        mActors[ position.y][ position.x] = actor;
        actor->setPosition( position );
    }

    int CMap::getLastestId() {
        return ++mCurrentId;
    }

    char CMap::getMapAt(const Vec2i &p) {

        if ( !isValid( p ) ) {
            return '.';
        }

        return mElement[p.y][p.x];
    }

    void CMap::floodFill(Vec2i position, char oldElement, char newElement) {
        if ( getMapAt( position ) == oldElement ) {
            mElement[ position.y ][ position.x ] = newElement;
            block[ position.y ][ position.x ] = false;
            map[ position.y ][ position.x ] = nullptr;
            floodFill( position + mapOffsetForDirection( EDirection::kNorth ), oldElement, newElement );
            floodFill( position + mapOffsetForDirection( EDirection::kEast ), oldElement, newElement );
            floodFill( position + mapOffsetForDirection( EDirection::kSouth ), oldElement, newElement );
            floodFill( position + mapOffsetForDirection( EDirection::kWest ), oldElement, newElement );
        }

    }

    std::shared_ptr<CGameDelegate> CMap::getGameDelegate() {
        return mGameDelegate;
    }
}
