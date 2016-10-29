//
// Created by monty on 25/10/16.
//
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <functional>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CGameDelegate.h"
#include "CActor.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CMoveActorCommand.h"

namespace Knights {

    CMoveActorCommand::CMoveActorCommand( EDirection aDirection ) : mDirection( aDirection ) {
    }

    std::string CMoveActorCommand::to_string() const {

        std::stringstream ss;
        ss << "Move actor by ";
        ss << mDirection;
        return ss.str();
    }

    bool CMoveActorCommand::shouldEndTurn() {
        return true;
    }

    void CMoveActorCommand::execute() {

    }
}