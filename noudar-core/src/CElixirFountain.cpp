//
// Created by monty on 31/12/16.
//
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CElixirFountain.h"
#include "CGameDelegate.h"
#include "CMap.h"


namespace Knights {
	CElixirFountain::CElixirFountain(int aId) : CActor(aId, 1) {
		mView = 'J';
		mTeam = ETeam::kVillains;
		mHP = 1;
		mAttack = 0;
		mDefence = 0;
		mName = "Elixir fountain";
	}
}