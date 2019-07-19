#include <string>
#include <memory>
#include <math.h>
#include <map>
#include <functional>
#include <EASTL/vector.h>
#include <EASTL/array.h>

using eastl::vector;
using eastl::array;

#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CCharacterArchetype.h"
#include "CCharacter.h"
#include "CMonster.h"
#include "CGameDelegate.h"
#include "CMap.h"

namespace Knights {

	CMonster::CMonster(std::shared_ptr<CCharacterArchetype> aArchetype, ETeam aTeam, ActorId aId, int aViewRange, CMonsterUpdateCallback updateCallback)
			: CCharacter(aArchetype, aTeam, aId), mUpdateCallback( updateCallback ), mViewRange( aViewRange) {
	}

    CMonster::CMonster(std::shared_ptr<CCharacterArchetype> aArchetype, ETeam aTeam, ActorId aId, int aViewRange )
            : CCharacter(aArchetype, aTeam, aId), mUpdateCallback( [](std::shared_ptr <CMap> map, std::shared_ptr<CActor> me){} ), mViewRange( aViewRange){
    }

	bool CMonster::dealWith(std::shared_ptr<CMap> map, int x, int y) {
		int dx = x - mPosition.x;
		int dy = y - mPosition.y;

		auto sharedThis = shared_from_this();

		if (abs(dx) >= abs(dy)) {

			if ( abs(dx) == 1) {
				map->attack( sharedThis, {x, y}, false);
				onMove();
				return true;
			}

			if (dx <= 0) {

                if (!map->move(EDirection::kWest, sharedThis)) {
					if (!map->move(EDirection::kSouth, sharedThis)) {
						return map->move(EDirection::kNorth, sharedThis);
					}
                }

                return true;
			} else if (dx > 0) {

                if (!map->move(EDirection::kEast, sharedThis)) {
					if (!map->move(EDirection::kNorth, sharedThis)) {
						return map->move(EDirection::kSouth, sharedThis);
					}
				}

                return true;
			}
		} else {
			if ( abs(dy) == 1) {
                map->attack( sharedThis, {x, y}, false);
                onMove();
				return true;
			}

			if (dy <= 0) {

                if (!map->move(EDirection::kNorth, sharedThis)) {
					if (!map->move(EDirection::kWest, sharedThis)) {
						return map->move(EDirection::kEast, sharedThis);
					}
                }

				return true;
			} else if (dy > 0) {

                if (!map->move(EDirection::kSouth, sharedThis)) {
					if (!map->move(EDirection::kEast, sharedThis)) {
						return map->move(EDirection::kWest, sharedThis);
					}
				}
                return true;
			}
		}

		return false;
	}

	bool CMonster::actOn(int newX, int newY, std::shared_ptr<CMap> map) {
		if (map->isValid({newX, newY})) {

			auto otherActor = map->getActorAt(Vec2i{newX, newY});

			if (otherActor != nullptr
			    && otherActor->getTeam() != getTeam()) {

				setTarget(otherActor);

				if (dealWith(map, newX, newY)) {
					return true;
				}
			}

			if (map->isBlockMovementAt({newX, newY})) {
				return false;
			}

		}
		return false;
	}

	void CMonster::update(std::shared_ptr<CMap> map) {

		CCharacter::update(map);
        mUpdateCallback(map, shared_from_this() );

		if ( mTarget != nullptr && getAP() > 0 && isAlive() ) {
			auto pos = mTarget->getPosition();
			actOn(pos.x, pos.y, map);
		} else {
			int newX;
			int newY;

			for (int x = -mViewRange / 2; x <= mViewRange / 2; ++x) {

				for (int y = -mViewRange / 2; y <= mViewRange / 2; ++y) {

					if (x == 0 && y == 0) {
						continue;
					}

					newX = std::min<int>(kMapSize - 1, std::max<int>(0, (x + mPosition.x)));
					newY = std::min<int>(kMapSize - 1, std::max<int>(0, (y + mPosition.y)));

					if (actOn(newX, newY, map)) {
						return;
					}
				}
			}
		}
	}
}