#include <memory>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CBullKnight.h"
#include "../include/CActor.h"

const int DEFAULT_AP = 5;

namespace Knights {

    CBullKnight::CBullKnight(int aId) : CActor(aId, DEFAULT_AP) {
        mView = '%';
        mTeam = ETeam::kHeroes;
        mHP = 10;
        mAttack = 5;
        mDefence = 2;
    }
}