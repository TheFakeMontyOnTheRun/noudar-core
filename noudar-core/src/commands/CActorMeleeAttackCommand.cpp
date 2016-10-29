//
// Created by monty on 25/10/16.
//
#include <string>
#include <sstream>
#include <memory>
#include "Vec2i.h"
#include "CActor.h"
#include "commands/IGameCommand.h"
#include "commands/CActorMeleeAttackCommand.h"

namespace Knights {

    CActorMeleeAttackCommand::CActorMeleeAttackCommand( float aStrength, std::shared_ptr<CActor> aTarget  ) : mStrength( aStrength ), mTarget( aTarget ) {
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

    }
}