//
// Created by monty on 25/10/16.
//
#include <string>
#include "commands/IGameCommand.h"
#include "commands/CEndTurnCommand.h"

namespace Knights {

    std::string CEndTurnCommand::to_string() const {
        return "Quit";
    }

    bool CEndTurnCommand::shouldEndTurn() {
        return true;
    }

    void CEndTurnCommand::execute() {
    }
}