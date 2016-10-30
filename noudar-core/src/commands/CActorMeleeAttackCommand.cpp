//
// Created by monty on 25/10/16.
//
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <functional>
#include "Vec2i.h"
#include "CActor.h"
#include "IRenderer.h"
#include "CGameDelegate.h"
#include "IMapElement.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CActorMeleeAttackCommand.h"

namespace Knights {

    CActorMeleeAttackCommand::CActorMeleeAttackCommand( std::shared_ptr<CGame> aGame, float aStrength, std::shared_ptr<CActor> aTarget  ) : mStrength( aStrength ), mTarget( aTarget ), IGameCommand( aGame ) {
    }

    std::string CActorMeleeAttackCommand::to_string() const {

        std::stringstream ss;
        ss << "melee attack with strength of ";
        ss << mStrength;
        ss << " to ";
        ss << mTarget->getName();
        return ss.str();
    }

    bool CActorMeleeAttackCommand::shouldEndTurn() {
        return true;
    }

    void CActorMeleeAttackCommand::execute() {

        auto map = getGame()->getMap();
        std::shared_ptr<CActor> actor = map->getAvatar();

        if ( nullptr == mTarget ) {
            return;
        }

        if (actor->getTeam() != mTarget->getTeam()) {
            actor->performAttack(mTarget);
        }
    }
}