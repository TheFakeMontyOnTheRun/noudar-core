#include <string>
#include <map>
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <array>

using std::vector;
using std::array;

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
#include "CMonsterGenerator.h"

namespace Knights {

    const auto kCrossbowAmmoUsage = 3;
    const auto kShieldPowerUsage = 5;
    const auto kImprovedDamageRatio = 10;
    const auto kRegularEnemyViewRange = 8;
    const auto kMonkViewRange = 4;
    const auto kMasterDemonViewRange = (3 * kMapSize) / 4;
    const static bool kPlaceEmptySpacesForSpawnPoints =
#if defined(__ANDROID__ ) || defined(__EMSCRIPTEN__) || defined(MESA_GLES2) || defined(TARGET_IOS)  || defined(TARGET_OSX) || defined(OSMESA) || defined(VGA)
            false;
#else
            true;
#endif

    void CMap::endOfTurn(uint32_t turn) {

        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {
                if (mActors[y][x] != nullptr) {
                    mActors[y][x]->endOfTurn();
                }
            }
        }

        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {
                auto actor = mActors[y][x];
                if (actor != nullptr && !actor->isAlive()) {
                    mActors[y][x] = nullptr;
                }
            }
        }

        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {
                auto actor = mActors[y][x];
                if (actor != nullptr && turn > actor->mLastUpdatedTurn) {
                    actor->mLastUpdatedTurn = turn;
                    actor->update(shared_from_this());
                }
            }
        }

    }

    std::shared_ptr<Knights::CItem> CMap::makeItemWithSymbol(char symbol ) {
        switch( symbol ) {
            case 'v':
                return std::make_shared<CStorageItem>("Shield of restoration", 'v', false, false, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){

                    auto shield = (CStorageItem*)aActor->getItemWithSymbol( 'v' ).get();

                    if ( shield  == nullptr ) {
                        return;
                    }

                    if ( shield->getAmount() > 0 ) {
                        aActor->addHP( 1 );
                        shield->add( -1 );
                    } else {
                        aActor->setCurrentSay("Shield depleted");
                    }

                }, 0);

            case 'y':
                return std::make_shared<CStorageItem>("Crossbow of damnation", 'y', false, false, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){

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
                        aMap->getAvatar()->setCurrentSay("Crossbow depleted");
                        return;
                    }

                    auto target = aMap->projectHitscanPosition(aMap->getActorTargetPosition(aActor),
                                                               aActor->getDirection());

                    if ( !( target == aActor->getPosition() ) ) {
                        aActor->setAttackBonus( 1 );
                        aMap->attack( aActor, target, false );

                        if ( shieldHasAmmo ) {
                            aActor->setAttackBonus( kImprovedDamageRatio );
                            aMap->attack( aActor, target, false );
                        }
                        aActor->setAttackBonus( 0 );
                    }

                    aMap->getGameDelegate()->onProjectileHit( target);

                    crossbow->add( - ( kCrossbowAmmoUsage ) );

                    if ( shieldHasAmmo ) {
                        shield->add( -( kShieldPowerUsage ) );
                        aMap->getAvatar()->setCurrentSay("Supercharged shot!");
                    }

                }, 0);
            case 'u':
                return std::make_shared<CStorageItem>("Quiver", 'u', false, true, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){}, 5);
            case '+':
                return std::make_shared<CItem>("The holy health", '+', true, true, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){
                    aActor->addHP(20);
                });
            default:
                return nullptr;
        }
    }

    CMap::CMap(const std::string &mapData, std::shared_ptr<CGameDelegate> aGameDelegate)
            : mGameDelegate(aGameDelegate) {

        ElementView element;
        std::shared_ptr<CActor> actor = nullptr;
        std::shared_ptr<CItem> item = nullptr;

        auto heroArchetype = std::make_shared<CCharacterArchetype>( 5, 3, 100, 7, '^', "Hero");
        auto fallenArchetype = std::make_shared<CCharacterArchetype>( 4, 1, 10, 3, '$', "Fallen Hero");
        auto monkArchetype = std::make_shared<CCharacterArchetype>( 4, 0, 10, 3, '@', "Insane Monk");
        auto cocoonArchetype = std::make_shared<CCharacterArchetype>( 0, 0, 10000, 0, 'C', "Cocoon");
        auto evilSpiritArchetype = std::make_shared<CCharacterArchetype>( 4, 5, 5, 3, 'w', "Evil Spirit");
        auto warthogArchetype = std::make_shared<CCharacterArchetype>( 6, 4, 10, 3, 'J', "Demon Warthog");
        auto weakenedDemonArchetype = std::make_shared<CCharacterArchetype>( 8, 3000, 10, 3, 'd', "Master Demon (premature)");
        auto demonArchetype = std::make_shared<CCharacterArchetype>( 12, 10, 50, 3, 'D', "Master Demon");
        auto friends = ETeam::kHeroes;
        auto foes = ETeam::kMonsters;
        int pos = 0;
        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {

                element = mapData[ pos ];
                actor = nullptr;
                item = nullptr;
                mElementsMap[y][x] = nullptr;
                mActors[ y ][ x ] = nullptr;
                mElement[y][x] = element;
                mItems[ y ][ x ] = nullptr;

                switch (element) {
                    case '0':
                    case 'O':
                    case '=':
                    case '_':
                    case '-':
                    case '(':
                    case ')':
                    case '~':
                    case '2':
                    case '{':
                    case '}':
                    case '7':
                    case '!':
                    case 'H':
                    case 'P':
                        break;
                    case '1':
                    case 'L':
                    case 'I':
                    case 'R':
                    case '@':
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
                        mTileBlockProperties[y][x].mBlockMovement = true;
                        break;
                    case 'K':
                    case 'A':
                        mTileBlockProperties[y][x].mBlockMovement = true;
                        break;
                    case '4':
                        actor = mAvatar = std::make_shared<CCharacter>( heroArchetype, friends, getLastestId(), [](std::shared_ptr<CActor> character, std::shared_ptr<CMap> map){
                            auto shield = (CStorageItem*)character->getItemWithSymbol( 'v' ).get();
                            if ( shield != nullptr && map->getElementAt( character->getPosition() ) == '*' ) {

                                if ( shield->getAmount() < 20 ) {
                                    map->getAvatar()->setCurrentSay("Holy items get charged on holy soil");
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

                        {
                            auto sword = std::make_shared<CItem>("Sword of sorrow", 't', false, false,
                                                                 [](std::shared_ptr<CActor> aActor,
                                                                    std::shared_ptr<CMap> aMap) {
                                                                     auto target = aMap->getActorTargetPosition(aActor);
                                                                     aMap->attack(aActor, target, true);
                                                                 });

                            actor->giveItem(sword);
                        }
                        break;

                    case '9':
                    {
                        mElementsMap[y][x] = std::make_shared<CDoorway>();
                        mElement[y][x] = mElementsMap[y][x]->getView();
                    }
                        break;
                    case '3':
                    case 'T':
                    {
                        auto ropeArchetype = std::make_shared<CCharacterArchetype>( 0,
                                                                                    element == 'T' ? 0 : 10,
                                                                                    10000, 0, element,
                                                                                    element == 'T' ? "Rope" : "Reenforced Door");

                        actor = std::make_shared<CCharacter>( ropeArchetype, foes, getLastestId(), [element](std::shared_ptr<CActor> character, std::shared_ptr<CMap> map){
                            auto archetype = ((CCharacter*)character.get())->getArchetype();

                            if ( archetype.getHP() > character->getHP() ) {
                                auto position = character->getPosition();
                                map->getAvatar()->setCurrentSay("You hear mechanisms in action");
                                map->floodFill( position,
                                                {
                                                        {'#', std::pair<ElementView , CBlockProperties>('~', CBlockProperties())},
                                                        {'H', std::pair<ElementView , CBlockProperties>('F', CBlockProperties(true, false, false))},
                                                        {element, std::pair<ElementView, CBlockProperties>('_', CBlockProperties()) },
                                                        {'R', std::pair<ElementView, CBlockProperties>('1', CBlockProperties{true, true, true}) }
                                                });
                                character->addHP( -character->getHP() );
                                map->removeActorFrom( character->getPosition() );
                            }

                        });
                        mTileBlockProperties[y][x].mBlockMovement = true;
                    }
                        break;
                    case 'w':
                        actor = std::make_shared<CMonster>( evilSpiritArchetype, foes, getLastestId(), kRegularEnemyViewRange );
                        break;

                    case 'J':
                        actor = std::make_shared<CMonster>( warthogArchetype, foes, getLastestId(), kRegularEnemyViewRange );
                        break;
                    case '6':
                        actor = std::make_shared<CMonster>( monkArchetype, foes, getLastestId(), kMonkViewRange, [](std::shared_ptr <CMap> map, std::shared_ptr<CActor> me) {

                            auto character = (CCharacter*)(me.get());
                            auto defaultHP = character->getArchetype().getHP();
                            auto currentHP = me->getHP();

                            if ( currentHP < defaultHP ) {
                                character->addHP( -character->getHP() );
                                auto position = me->getPosition();
                                auto px = me->getPosition().x;
                                auto py = me->getPosition().y;
                                map->removeActorFrom( position );

                                map->mItems[ py ][ px ] = std::make_shared<CItem>("The holy health", '+', true, true, [](std::shared_ptr<CActor> aActor, std::shared_ptr<CMap> aMap){
                                    aActor->addHP(20);
                                });
                            }
                        });
                        break;
                    case '5':
                        actor = std::make_shared<CMonster>( fallenArchetype, foes, getLastestId(), kRegularEnemyViewRange );
                        break;
                    case 'c':
                        actor = std::make_shared<CMonster>( cocoonArchetype, foes, getLastestId(), 0, [weakenedDemonArchetype, foes](std::shared_ptr <CMap> map, std::shared_ptr<CActor> me) {

                            auto character = (CCharacter*)(me.get());
                            auto defaultHP = character->getArchetype().getHP();
                            auto currentHP = me->getHP();

                            if ( currentHP < defaultHP ) {
                                character->addHP( -character->getHP() );
                                auto position = me->getPosition();
                                map->removeActorFrom( position );
                                map->addActorAt( std::make_shared<CMonster>( weakenedDemonArchetype, foes, map->getLastestId(), kMasterDemonViewRange), position );
                            }
                        });
                        break;
                    case 'd':
                        actor = std::make_shared<CMonster>( weakenedDemonArchetype, foes, getLastestId(), kMasterDemonViewRange);
                        break;
                    case 'e':
                        actor = std::make_shared<CMonster>( demonArchetype, foes, getLastestId(), kMasterDemonViewRange );
                        break;

                    case 'G':
                        actor = std::make_shared<CMonsterGenerator>( evilSpiritArchetype, foes, getLastestId(), 5);
                        break;
                    default:
                        item = makeItemWithSymbol(element);

                }

                if (actor != nullptr) {
                    mActors[y][x] = actor;

                    if (kPlaceEmptySpacesForSpawnPoints && element != '3' && element != 'T' ) {
                        mElement[y][x] = '.';
                    } else {
                        mElement[y][x] = element;
                    }

                    actor->setPosition({x, y});
                    actor = nullptr;
                } else if ( item != nullptr ) {
                    mItems[ y ][ x ] = item;

                    if (kPlaceEmptySpacesForSpawnPoints) {
                        mElement[y][x] = '.';
                    } else {
                        mElement[y][x] = element;
                    }
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
            otherActor->setTarget(actor);

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

    bool CMap::move(EDirection d, std::shared_ptr<CActor> actor) {

        if (!actor->canMove()) {
            return false;
        }

        auto position = actor->getPosition();
        auto offset = mapOffsetForDirection( d );
        auto newPosition = position + offset;

        if (!isBlockMovementAt(newPosition)) {
            moveActor(position, newPosition, actor);
            actor->onMove();
            return true;
        }

        return false;
    }

    bool CMap::isValid(const Vec2i& p) {
        if (p.x < 0 || p.x >= kMapSize || p.y < 0 || p.y >= kMapSize) {
            return false;
        }
        return true;
    }

    bool CMap::isBlockMovementAt(const Vec2i &p) {

        if (!isValid(p)) {
            return true;
        }

        if (mActors[p.y][p.x] != nullptr) {
            return true;
        }
        return mTileBlockProperties[p.y][p.x].mBlockMovement;
    }

    std::shared_ptr<CActor> CMap::getActorAt(Vec2i position) {
        if ( isValid( position ) ) {
            return mActors[position.y][position.x];
        } else {
            return nullptr;
        }
    }

    ElementView CMap::getElementAt(const Vec2i& p) {

        if ( !isValid( p ) ) {
            return kEmptySpace;
        }

        return mElement[p.y][p.x];
    }

    std::shared_ptr<CActor> CMap::getAvatar() {
        return mAvatar;
    }

    void CMap::setActorAt(Vec2i position, std::shared_ptr<CActor> actor) {

        if ( !isValid(position)) {
            return;
        }

        mActors[position.y][position.x] = actor;
    }

    bool CMap::isLevelFinished() {

        auto position = this->getAvatar()->getPosition();

        if ( !isValid(position)) {
            return false;
        }

        int monsters = 0;
        bool hasExit = false;
        auto heroTeam = getAvatar()->getTeam();

        for (int y = 0; y < kMapSize; ++y) {
            for (int x = 0; x < kMapSize; ++x) {

                if ( mElement[ y ][ x ] == 'E' ) {
                    hasExit = true;
                }

                if (mActors[y][x] != nullptr) {
                    auto actor = mActors[ y ][ x ];
                    if ( actor->isAlive() && actor->getTeam() != heroTeam ) {
                        monsters++;
                    }
                }
            }
        }

        if ( monsters == 0 && !hasExit ) {
            return true;
        }

        return mElement[position.y][position.x] == 'E';
    }

    void CMap::moveActor(Vec2i from, Vec2i to, std::shared_ptr<CActor> actor) {
        if ( !isValid(from) || !isValid(to)) {
            return;
        }

        mActors[from.y][from.x] = nullptr;
        mActors[to.y][to.x] = actor;
        actor->setPosition(to);
    }

    Vec2i CMap::projectHitscanPosition(Vec2i aPosition, EDirection aDirection) {

        auto offset = mapOffsetForDirection( aDirection );
        auto position = aPosition;
        std::shared_ptr<CActor> toReturn = nullptr;

        auto previous = position;
        while ( isValid( position ) && !isBlockProjectilesAt(position) ) {

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

#ifdef USE_ITEMS_INSTANTLY
            if( item->isConsumable() ) {
                useItem( item, actor );
            }
#endif
        }
    }

    std::shared_ptr<Knights::CItem> CMap::getItemAt( Vec2i from ) {

        if ( !isValid( from ) ) {
            return nullptr;
        }

        return mItems[ from.y ][ from.x ];
    }

    void CMap::putItemAt(std::shared_ptr<CItem> aItem, Vec2i aDestination) {

        if ( !isValid(aDestination)) {
            return;
        }

        if ( mItems[ aDestination.y ][ aDestination.x ] == nullptr ) {
            mItems[ aDestination.y ][ aDestination.x ] = aItem;
        }
    }

    void CMap::addActorAt(std::shared_ptr<CActor> actor, const Vec2i &position) {

        if ( !isValid(position)) {
            return;
        }

        mElement[ position.y ][ position.x ] = '.';
        mActors[ position.y][ position.x] = actor;
        actor->setPosition( position );
    }

    ActorId CMap::getLastestId() {
        return ++mCurrentId;
    }

    void CMap::floodFill(Vec2i position, std::map<char, std::pair<ElementView, CBlockProperties>> transformations ) {
        auto oldElement = getElementAt( position );
        if ( transformations.count( oldElement ) > 0 ) {

            auto newElement = transformations[ oldElement ];
            mElement[ position.y ][ position.x ] = newElement.first;
            mTileBlockProperties[position.y][position.x] = newElement.second;
            mElementsMap[ position.y ][ position.x ] = nullptr;
            floodFill( position + mapOffsetForDirection( EDirection::kNorth ), transformations );
            floodFill( position + mapOffsetForDirection( EDirection::kEast ), transformations );
            floodFill( position + mapOffsetForDirection( EDirection::kSouth ), transformations );
            floodFill( position + mapOffsetForDirection( EDirection::kWest ), transformations );

        }
    }

    std::shared_ptr<CGameDelegate> CMap::getGameDelegate() {
        return mGameDelegate;
    }

    Vec2i CMap::getTargetProjection(std::shared_ptr<CActor> a) {
        auto target = getActorTargetPosition( a );

        if ( a->getSelectedItem() != nullptr && a->getSelectedItem()->getView() == 'y' ) {
            return projectHitscanPosition(target, a->getDirection());
        }

        return target;
    }

    bool CMap::isBlockProjectilesAt(const Vec2i &p) {

        if (!isValid(p)) {
            return true;
        }

        if (mActors[p.y][p.x] != nullptr) {
            return true;
        }
        return mTileBlockProperties[p.y][p.x].mBlockProjectile;
    }

    bool CMap::isBlockViewAt(const Vec2i &p) {

        if (!isValid(p)) {
            return true;
        }

        return mTileBlockProperties[p.y][p.x].mBlockView;
    }

    void CMap::removeActorFrom(Vec2i position) {
        if (!isValid(position)) {
            return;
        }

        auto actor = getActorAt( position );
        actor->setPosition({-1, -1});
        mActors[ position.y ][ position.x ] = nullptr;
    }

    ItemView CMap::getItemViewAt(const Vec2i &p) {

        if ( isValid( p ) ) {
            auto item = mItems[p.y][p.x];

            if (item != nullptr) {
                return item->getView();
            }
        }

        return kEmptySpace;
    }

    void CMap::useItem(std::shared_ptr<CItem> item, std::shared_ptr<CActor> actor) {

        item->use(actor, shared_from_this());

        if ( item->isConsumable() ) {
            actor->removeItemFromInventory(item);
        }
    }
}
