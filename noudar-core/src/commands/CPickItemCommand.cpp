//
// Created by monty on 13/02/17.
//

#ifdef USE_IOSTREAM
#include <sstream>
#endif

#include <string>
#include <memory>
#include <functional>
#include <utility>
#include <map>
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
	auto previousItem = mActor->getSelectedItem()->getView();
    auto item = map->getItemAt(map->getActorTargetPosition(mActor));
    bool giveBack = false;
    if (item != nullptr ) {
        giveBack = item->isConsumable();
        mItemName = item->to_string();
    }
	map->giveItemAt( map->getActorTargetPosition(mActor), mActor );
#ifdef USE_ITEMS_INSTANTLY
    if (giveBack) {
        mActor->suggestCurrentItem(previousItem);
    }
#endif
}
