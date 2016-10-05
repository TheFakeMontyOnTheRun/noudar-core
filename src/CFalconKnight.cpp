#include <memory>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CFalconKnight.h"
#include "../include/CActor.h"

const int DEFAULT_AP = 6;

namespace Knights {

    CFalconKnight::CFalconKnight(int aId) : CActor(aId, DEFAULT_AP) {
        mView = '&';
        mTeam = ETeam::kHeroes;
        mHP = 2;
        mAttack = 3;
        mDefence = 3;
    }
}