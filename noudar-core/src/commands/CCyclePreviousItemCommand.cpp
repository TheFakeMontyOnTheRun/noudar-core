//
// Created by monty on 12/02/17.
//

#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include "Vec2i.h"
#include "IMapElement.h"
#include "CGameDelegate.h"
#include <string>
#include <memory>
#include <utility>
#include <map>
#include <EASTL/vector.h>
#include <EASTL/array.h>

using eastl::vector;
using eastl::array;

#include "Vec2i.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "CGame.h"
#include "commands/IGameCommand.h"

#include "commands/CCyclePreviousItemCommand.h"

namespace Knights {
	CCyclePreviousItemCommand::CCyclePreviousItemCommand( std::shared_ptr<CGame> aGame, std::shared_ptr<CActor> aActor ) : IGameCommand( aGame ), mActor(aActor){
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
}