//
// Created by monty on 25/10/16.
//

#include <string>
#include <memory>
#include <functional>
#include <map>
#include <EASTL/vector.h>
#include <EASTL/array.h>

using eastl::vector;
using eastl::array;

#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CGame.h"
#include "commands/IGameCommand.h"

namespace Knights {

    IGameCommand::IGameCommand(std::shared_ptr<CGame> aGame) : mGame(aGame) {
    }

    std::shared_ptr<CGame> IGameCommand::getGame() {
        return mGame;
    }

    std::string to_string(const IGameCommand &action) {
        return action.to_string();
    }
}
