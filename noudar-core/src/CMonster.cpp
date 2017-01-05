#include <string>
#include <vector>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <functional>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CActor.h"
#include "CCharacterArchetype.h"
#include "CCharacter.h"
#include "CMonster.h"
#include "CGameDelegate.h"
#include "CMap.h"

namespace Knights {

    CMonster::CMonster(std::shared_ptr<CCharacterArchetype> aArchetype, std::shared_ptr<CTeam> aTeam, int aId) : CCharacter( aArchetype, aTeam, aId ) {
    }

    bool CMonster::dealWith( std::shared_ptr<CMap> map, int x, int y ) {
            int dx = x - mPosition.x;
            int dy = y - mPosition.y;

            std::shared_ptr<CMonster> sharedThis = shared_from_this();

            if ( std::abs( (float)dx ) > std::abs( (float)dy ) ) {

                    if ( dx < 0 ) {
                            map->move( EDirection::kWest, sharedThis );
                            return true;
                    } else if ( dx > 0 ) {
                            map->move( EDirection::kEast, sharedThis );
                            return true;
                    }
            } else {

                    if ( dy < 0 ) {
                            map->move( EDirection::kNorth, sharedThis );
                            return true;
                    } else if (dy > 0 ){
                            map->move( EDirection::kSouth, sharedThis );
                            return true;
                    }
            }

            return false;
    }

    bool CMonster::actOn( int newX, int newY,  std::shared_ptr<CMap> map ) {

            if (map->isValid( newX, newY ) ) {

                    auto otherActor = map->getActorAt( Vec2i{ newX, newY } );

                    if (otherActor != nullptr
                        && otherActor->getTeam() != getTeam()) {

                            if (dealWith( map, newX, newY ) ) {
                                    return true;
                            }
                    }

                    if ( map->isBlockAt( newX, newY ) ) {
                            return false;
                    }

            }
            return false;
    }

    void CMonster::update( std::shared_ptr<CMap> map ) {

            int newX;
            int newY;

            for (int x = -10; x < 10; ++x) {

                    for (int y = -10; y < 10; ++y) {

                            if ( x == 0 && y == 0 ) {
                                    continue;
                            }

                            newX = std::min<int>( kMapSize, std::max<int>( 0, (x + mPosition.x) ));
                            newY = std::min<int>( kMapSize, std::max<int>( 0, (y + mPosition.y) ));

                            if (actOn(newX, newY, map)) {
	                            return;
                            }
                    }
            }
    }

    void CMonster::endOfTurn() {

    }
}