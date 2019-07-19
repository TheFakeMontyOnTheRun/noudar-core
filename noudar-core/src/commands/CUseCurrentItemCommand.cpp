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
#include "commands/CUseCurrentItemCommand.h"

Knights::CUseCurrentItemCommand::CUseCurrentItemCommand(std::shared_ptr<Knights::CGame> aGame,
                                                        std::shared_ptr<Knights::CActor> aActor) :
IGameCommand( aGame ), mActor( aActor ) {
}

std::string Knights::CUseCurrentItemCommand::to_string() const {
	std::string message = "Use item: ";
	message.append(mItemName);
	return message;
}

bool Knights::CUseCurrentItemCommand::shouldEndTurn() {
	return true;
}

void Knights::CUseCurrentItemCommand::execute() {

	auto currentItem = mActor->getSelectedItem();

	if ( currentItem != nullptr ) {
		getGame()->getMap()->useItem( currentItem, mActor );
		mItemName = currentItem->to_string();
	}
}
