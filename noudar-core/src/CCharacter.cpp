#include <string>
#include <vector>
#include <cstdlib>
#include <memory>
#include <cmath>
#include <functional>
#include "Vec2i.h"
#include "CTeam.h"
#include "IMapElement.h"
#include "CItem.h"
#include "CActor.h"
#include "CCharacterArchetype.h"
#include "CCharacter.h"

//const int DEFAULT_AP = 7;
namespace Knights {

	CCharacter::CCharacter(std::shared_ptr<Knights::CCharacterArchetype> aArchetype, std::shared_ptr<CTeam> aTeam, int aId) :
	CActor( aId, aArchetype->getAP()) {
        mView = aArchetype->getView();
        mTeam = aTeam;
        mHP = aArchetype->getHP();
        mAttack = aArchetype->getAttack();
        mDefence = aArchetype->getDefense();
        mName = aArchetype->getName();
	}
}
