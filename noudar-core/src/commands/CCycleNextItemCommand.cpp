//
// Created by monty on 12/02/17.
//

#ifdef USE_IOSTREAM
#include <sstream>
#endif

#include <memory>
#include <functional>
#include <string>
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
#include "CPlainFileLoader.h"
#include "CGame.h"
#include "commands/IGameCommand.h"
#include "commands/CCycleNextItemCommand.h"

namespace Knights {
	CCycleNextItemCommand::CCycleNextItemCommand(std::shared_ptr <CGame> aGame, std::shared_ptr <CActor> aActor	): IGameCommand( aGame ), mActor(aActor) {
	}

	std::string CCycleNextItemCommand::to_string() const {
		return "Next item";
	}

	bool CCycleNextItemCommand::shouldEndTurn() {
		return false;
	}

	void CCycleNextItemCommand::execute() {
		mActor->selectNextItem();
	}
}