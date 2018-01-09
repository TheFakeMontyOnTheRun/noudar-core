//
// Created by monty on 25/10/16.
//

#ifdef USE_IOSTREAM
#include <sstream>
#endif

#include <string>
#include <memory>
#include <map>
#include <functional>
#include <EASTL/vector.h>
#include <EASTL/array.h>

using eastl::vector;
using eastl::array;

#include "Vec2i.h"
#include "IMapElement.h"
#include "CGameDelegate.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"
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
#ifdef USE_IOSTREAM
        std::stringstream ss;
        ss << "Move actor by ";
        ss << mDirection;
        return ss.str();
#else
        auto directions = "NESW";
        auto direction = directions[static_cast<int>(mDirection)];

        return std::string("Turn to ") + direction;
#endif
    }

    bool CTurnActorCommand::shouldEndTurn() {
        return false;
    }

    void CTurnActorCommand::execute() {

        mActor->setDirection(mDirection);
    }
}
