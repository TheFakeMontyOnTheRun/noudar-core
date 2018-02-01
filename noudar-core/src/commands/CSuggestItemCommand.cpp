//
// Created by monty on 13/02/17.
//

#ifdef USE_IOSTREAM
#include <sstream>
#endif

#include <string>
#include <functional>
#include <memory>
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
#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CSuggestItemCommand.h"

Knights::CSuggestItemCommand::CSuggestItemCommand(std::shared_ptr<Knights::CGame> aGame,
                                            std::shared_ptr<Knights::CActor> aActor, ElementView itemView) : IGameCommand( aGame ), mActor( aActor ), mItemView(itemView) {
}

std::string Knights::CSuggestItemCommand::to_string() const {
    std::string message = "Select item: ";
    auto item = mActor->getItemWithSymbol(mItemView);

    if ( item == nullptr ) {
        return "";
    }

    message.append( item->to_string() );
	return message;
}

bool Knights::CSuggestItemCommand::shouldEndTurn() {
	return false;
}

void Knights::CSuggestItemCommand::execute() {
	mActor->suggestCurrentItem(mItemView);
}
