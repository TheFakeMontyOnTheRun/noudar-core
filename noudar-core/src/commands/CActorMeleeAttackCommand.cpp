//
// Created by monty on 25/10/16.
//
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <functional>
#include "Vec2i.h"
#include "CTeam.h"
#include "CActor.h"
#include "IRenderer.h"
#include "CGameDelegate.h"
#include "IMapElement.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CActorMeleeAttackCommand.h"

namespace Knights {

    CActorMeleeAttackCommand::CActorMeleeAttackCommand(std::shared_ptr<CGame> aGame,
                                                       std::shared_ptr<CActor> aAttacker,
                                                       std::shared_ptr<CActor> aTarget) :
            IGameCommand(aGame),
            mAttacker(aAttacker), mTarget(aTarget) {
    }

    std::string CActorMeleeAttackCommand::to_string() const {

        std::stringstream ss;
        ss << "melee attack from ";
        ss << mAttacker->getName();
        ss << " to ";
        ss << mTarget->getName();
        return ss.str();
    }

    bool CActorMeleeAttackCommand::shouldEndTurn() {
        return true;
    }

    void CActorMeleeAttackCommand::execute() {
        mAttacker->performAttack(mTarget);
    }
}
