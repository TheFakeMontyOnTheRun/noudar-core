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
#include "commands/CCycleNextItemCommand.h"

namespace Knights {
	CCycleNextItemCommand::CCycleNextItemCommand(std::shared_ptr <CGame> aGame, std::shared_ptr <CActor> aActor	): IGameCommand( aGame ), mActor(aActor) {
	}

	std::string CCycleNextItemCommand::to_string() const {
		if ( mItemName.empty()) {
			return "";
		} else {
			std::string message = "Next item: ";
			message.append(mItemName);
			return message;
		}
	}

	bool CCycleNextItemCommand::shouldEndTurn() {
		return false;
	}

	void CCycleNextItemCommand::execute() {
		auto previousItemSymbol = mActor->getSelectedItem()->getView();
		mActor->selectNextItem();
		auto itemSymbol = mActor->getSelectedItem()->getView();

		if ( previousItemSymbol != itemSymbol) {
			mItemName = mActor->getSelectedItem()->to_string();
		}
	}

    CCycleNextItemCommand::~CCycleNextItemCommand() {
	}
}