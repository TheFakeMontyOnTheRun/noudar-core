//
// Created by monty on 25/10/16.
//
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "CGame.h"

#include "commands/IGameCommand.h"
#include "commands/CNullCommand.h"

namespace Knights {

    CNullCommand::CNullCommand( std::shared_ptr<CGame> aGame ) : IGameCommand( aGame ) {
    }

    std::string CNullCommand::to_string() const {
        return "null";
    }

    bool CNullCommand::shouldEndTurn() {
        return false;
    }

    void CNullCommand::execute() {
    }
}