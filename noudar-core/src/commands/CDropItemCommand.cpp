//
// Created by monty on 13/02/17.
//

#include <string>
#include <functional>
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
#include "commands/CDropItemCommand.h"

Knights::CDropItemCommand::CDropItemCommand(std::shared_ptr<Knights::CGame> aGame,
                                            std::shared_ptr<Knights::CActor> aActor) : IGameCommand(aGame),
                                                                                       mActor(aActor) {
}

std::string Knights::CDropItemCommand::to_string() const {
    return "Drop item";
}

bool Knights::CDropItemCommand::shouldEndTurn() {
    return true;
}

void Knights::CDropItemCommand::execute() {
    auto itemToDrop = mActor->getSelectedItem();

    if (itemToDrop == nullptr) {
        return;
    }

    if (!itemToDrop->canBeDropped()) {
        return;
    }

    auto map = getGame()->getMap();
    auto target = map->getActorTargetPosition(mActor);

    if (map->isBlockMovementAt(target)) {
        return;
    }

    if (map->getItemAt(target) != nullptr) {
        return;
    }

    map->putItemAt(mActor->removeItemFromInventory(itemToDrop), target);
}

Knights::CDropItemCommand::~CDropItemCommand() {
}
