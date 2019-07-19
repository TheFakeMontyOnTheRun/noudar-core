//
// Created by monty on 25/10/16.
//

#include <string>
#include <memory>
#include <map>
#include <functional>
#include <vector>
#include <array>

using std::vector;
using std::array;

#include "Vec2i.h"
#include "IMapElement.h"
#include "CGameDelegate.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CTurnActorCommand.h"

namespace Knights {

    CTurnActorCommand::CTurnActorCommand(std::shared_ptr<CGame> aGame, EDirection aDirection,
                                         std::shared_ptr<CActor> aActor) :
            IGameCommand(aGame),
            mDirection(aDirection),
            mActor(aActor) {
    }

    std::string CTurnActorCommand::to_string() const {
        auto directions = "NESW";
        auto direction = directions[static_cast<int>(mDirection)];

        return std::string("Turn to ") + direction;
    }

    bool CTurnActorCommand::shouldEndTurn() {
        return false;
    }

    void CTurnActorCommand::execute() {

        mActor->setDirection(mDirection);
    }
}
