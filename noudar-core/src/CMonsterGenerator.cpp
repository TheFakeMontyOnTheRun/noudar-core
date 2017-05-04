//
// Created by monty on 29-03-2017.
//
#include <array>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <map>
#include <functional>
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

#include "CMonsterGenerator.h"

Knights::CMonsterGenerator::CMonsterGenerator(int aId, int aliveForTurns) : CActor(aId, 1) {
    mHP = aliveForTurns;
}

void Knights::CMonsterGenerator::update(std::shared_ptr<Knights::CMap> map) {
    CActor::update(map);

    --mHP;
    auto position = getPosition();
    auto monsterArchetype = std::make_shared<CCharacterArchetype>( 4, 1, 10, 3, '@', "Monster");
    auto id = map->getLastestId();
    auto foes = std::make_shared<CTeam>("Enemies");

    if ( map->getActorAt( { position.x, position.y - 1 } ) == nullptr ) {
        map->addActorAt( std::make_shared<CMonster>( monsterArchetype, foes, id), { position.x, position.y - 1 }  );
    } else if ( map->getActorAt( { position.x, position.y + 1 } ) == nullptr ) {
        map->addActorAt( std::make_shared<CMonster>( monsterArchetype, foes, id), { position.x, position.y + 1 }  );
    } else if ( map->getActorAt( { position.x - 1, position.y } ) == nullptr ) {
        map->addActorAt( std::make_shared<CMonster>( monsterArchetype, foes, id), { position.x - 1, position.y - 1 }  );
    } else if ( map->getActorAt( { position.x + 1, position.y } ) == nullptr ) {
        map->addActorAt( std::make_shared<CMonster>( monsterArchetype, foes, id), { position.x + 1, position.y - 1 }  );
    }
}
