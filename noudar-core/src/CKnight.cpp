#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CKnight.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"

const int DEFAULT_AP = 5;

namespace Knights {

    CKnight::CKnight(int aId) : CActor(aId, DEFAULT_AP) {
        mView = '%';
        mTeam = ETeam::kHeroes;
        mHP = 20;
        mAttack = 5;
        mDefence = 2;
        mName = "Hero";
    }

    void CKnight::update(std::shared_ptr <CMap> map) {

    }
}