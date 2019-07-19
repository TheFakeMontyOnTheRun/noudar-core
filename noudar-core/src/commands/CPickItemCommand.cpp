//
// Created by monty on 13/02/17.
//

#include <string>
#include <memory>
#include <functional>
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
#include "commands/CPickItemCommand.h"

Knights::CPickItemCommand::CPickItemCommand(std::shared_ptr<Knights::CGame> aGame,
                                            std::shared_ptr<Knights::CActor> aActor) : IGameCommand( aGame ), mActor(aActor) {
}

std::string Knights::CPickItemCommand::to_string() const {
    if ( mItemName.empty()) {
        return "";
    } else {
        std::string message = "Pick item: ";
        message.append(mItemName);
        return message;
    }
}

bool Knights::CPickItemCommand::shouldEndTurn() {
	return true;
}

void Knights::CPickItemCommand::execute() {
	auto map = getGame()->getMap();
#ifdef USE_ITEMS_INSTANTLY
	auto previousItem = mActor->getSelectedItem()->getView();
    bool giveBack = false;
#endif
    auto item = map->getItemAt(map->getActorTargetPosition(mActor));

    if (item != nullptr ) {
#ifdef USE_ITEMS_INSTANTLY
        giveBack = item->isConsumable();
#endif
        mItemName = item->to_string();
    }
	map->giveItemAt( map->getActorTargetPosition(mActor), mActor );
#ifdef USE_ITEMS_INSTANTLY
    if (giveBack) {
        mActor->suggestCurrentItem(previousItem);
    }
#endif
}

Knights::CPickItemCommand::~CPickItemCommand() {
}
