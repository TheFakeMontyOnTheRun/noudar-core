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
#include "commands/CTurnActorCommand.h"

namespace Knights {

    CTurnActorCommand::CTurnActorCommand( int aDegress ) : mDegrees( aDegress ) {
    }

    std::string CTurnActorCommand::to_string() const {

        std::stringstream ss;
        ss << "Turn actor by ";
        ss << mDegrees << " degrees";
        return ss.str();
    }

    bool CTurnActorCommand::shouldEndTurn() {
        return false;
    }

    void CTurnActorCommand::execute() {

    }
}