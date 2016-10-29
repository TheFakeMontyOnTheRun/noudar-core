//
// Created by monty on 25/10/16.
//
#include <string>
#include "commands/IGameCommand.h"
#include "commands/CQuitCommand.h"

namespace Knights {

    std::string CQuitCommand::to_string() const {

        return "Quit";
    }

    bool CQuitCommand::shouldEndTurn() {
        return false;
    }

    void CQuitCommand::execute() {

    }
}