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
#include "commands/CMoveActorCommand.h"

namespace Knights {

    CMoveActorCommand::CMoveActorCommand(std::shared_ptr<CGame> aGame, EDirection aDirection,
                                         std::shared_ptr<CActor> aActor) :
            IGameCommand(aGame),
            mDirection(aDirection),
            mActor(aActor) {
    }

    std::string CMoveActorCommand::to_string() const {
        auto directions = "NESW";
        auto direction = directions[static_cast<int>(mDirection)];

        return std::string("Move to ") + direction;
    }

    bool CMoveActorCommand::shouldEndTurn() {
        return true;
    }

    void CMoveActorCommand::execute() {
        std::shared_ptr<CMap> map = getGame()->getMap();

        map->move(mDirection, mActor);
    }
}
