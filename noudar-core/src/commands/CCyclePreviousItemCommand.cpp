//
// Created by monty on 12/02/17.
//

#include <memory>
#include <functional>
#include <string>
#include <memory>
#include <utility>
#include <map>
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
#include "commands/CCyclePreviousItemCommand.h"

namespace Knights {
    CCyclePreviousItemCommand::CCyclePreviousItemCommand(std::shared_ptr<CGame> aGame, std::shared_ptr<CActor> aActor)
            : IGameCommand(aGame), mActor(aActor) {
    }

    std::string CCyclePreviousItemCommand::to_string() const {
        return "Previous item";
    }

    bool CCyclePreviousItemCommand::shouldEndTurn() {
        return false;
    }

    void CCyclePreviousItemCommand::execute() {
        mActor->selectNextItem();
    }

    CCyclePreviousItemCommand::~CCyclePreviousItemCommand() {
    }
}