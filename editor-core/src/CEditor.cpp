//
// Created by monty on 03/01/17.
//

#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "CDoorway.h"
#include "CKnight.h"
#include "CMonster.h"
#include "IRenderer.h"

#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "CEditor.h"

namespace Knights {

	void CEditor::tick() {



//			std::shared_ptr <IGameCommand> command;

//			auto entry = mRenderer->getInput();

//			if (command != nullptr) {
//				command->execute();
//
//				if (command->shouldEndTurn()) {
//					endOfTurn(mMap);
//				}
//			}

			std::shared_ptr <CActor> avatar = mMap->getAvatar();
			mRenderer->drawMap(*mMap, avatar);
	}

	CEditor::CEditor(std::shared_ptr<IFileLoaderDelegate> fileLoaderDelegate, std::shared_ptr <IRenderer> aRenderer) :
			mRenderer(aRenderer), mFileLoaderDelegate(fileLoaderDelegate) {
	}

	Vec2i CEditor::getCursorPosition() {
		return mMap->getActorTargetPosition( mMap->getAvatar() );
	}

	std::shared_ptr <CMap> CEditor::getMap() {
		return mMap;
	}
}


