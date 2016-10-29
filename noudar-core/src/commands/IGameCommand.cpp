//
// Created by monty on 25/10/16.
//
#include <string>
#include "commands/IGameCommand.h"

namespace Knights {

    std::ostream& operator<<(std::ostream& os, const IGameCommand& action) {

        os << to_string( action );
        return os;
    }


    std::string to_string( const IGameCommand& action ) {
        return action.to_string();
    }
}