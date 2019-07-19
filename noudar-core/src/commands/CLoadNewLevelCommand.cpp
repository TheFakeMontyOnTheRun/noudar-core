//
// Created by monty on 08/12/16.
//

#include <string>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <array>

using std::vector;
using std::array;

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
#include "commands/CLoadNewLevelCommand.h"

namespace Knights {

    CLoadNewLevelCommand::CLoadNewLevelCommand(std::shared_ptr<CGame> aGame, int mapSlot)
            : IGameCommand(aGame), mMapSlot(mapSlot) {
    }

    std::string CLoadNewLevelCommand::to_string() const {
        return "Load new map";
    }

    bool CLoadNewLevelCommand::shouldEndTurn() {
        return true;
    }

    void CLoadNewLevelCommand::execute() {
        getGame()->playLevel(mMapSlot);
    }

    CLoadNewLevelCommand::~CLoadNewLevelCommand() {
    }
}