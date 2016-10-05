#include <memory>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CCuco.h"

const int DEFAULT_AP = 7;
namespace Knights {

    CCuco::CCuco() : CActor(DEFAULT_AP) {
        mView = '@';
        mTeam = ETeam::kVillains;
        mHP = 5;
        mAttack = 4;
        mDefence = 1;
    }
}