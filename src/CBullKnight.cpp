#include <memory>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CBullKnight.h"
#include "CActor.h"

const int DEFAULT_AP = 5;

namespace Knights {

    CBullKnight::CBullKnight(int aId) : CActor(aId, DEFAULT_AP) {
        mView = '%';
        mTeam = ETeam::kHeroes;
        mHP = 40;
        mAttack = 5;
        mDefence = 2;
    }
}