#include <memory>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CTurtleKnight.h"

const int DEFAULT_AP = 4;

namespace Knights {
    CTurtleKnight::CTurtleKnight() : CActor(DEFAULT_AP) {
        mView = '^';
        mTeam = ETeam::kHeroes;
        mHP = 30;
        mAttack = 2;
        mDefence = 5;
    }
}
