//
// Created by monty on 30/01/17.
//
#include <array>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <functional>
#include "Vec2i.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "IRenderer.h"
#include "CGameDelegate.h"
#include "IMapElement.h"
#include "CMap.h"
#include "IRenderer.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "CGame.h"
#include "commands/IGameCommand.h"

#include "commands/CHitscanAttackCommand.h"

Knights::CHitscanAttackCommand::CHitscanAttackCommand(std::shared_ptr<Knights::CGame> aGame,
                                                      std::shared_ptr<Knights::CActor> aAttacker) :
		IGameCommand(aGame),
		mAttacker(aAttacker) {

}

std::string Knights::CHitscanAttackCommand::to_string() const {
	return "Hitscan attack";
}

bool Knights::CHitscanAttackCommand::shouldEndTurn() {
	return true;
}

void Knights::CHitscanAttackCommand::execute() {
	auto target = getGame()->getMap()->projectLineOfSight( mAttacker->getPosition(), mAttacker->getDirection() );

	if ( target != nullptr ) {
	  getGame()->getMap()->attack( mAttacker, target->getPosition(), false );
	}
}
