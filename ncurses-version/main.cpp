/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/

#include <utility>
#include <functional>
#include <string>
#include <memory>
#include <array>
#include <map>
#include <EASTL/vector.h>

using eastl::vector;
using std::array;

#include "Common.h"
#include "IFileLoaderDelegate.h"
#include "CPlainFileLoader.h"

#include "Vec2i.h"
#include "IMapElement.h"
#include "CTeam.h"
#include "CItem.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CConsoleRenderer.h"
#include "CGame.h"
#include "commands/IGameCommand.h"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line) {
    return malloc( size );
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName,
                     int flags, unsigned debugFlags, const char* file, int line) {
    return malloc( size );
}

int main ( int argc, char **argv ) {
    const auto LEVEL_LIMIT = 7;

    auto delegate = std::make_shared<Knights::CGameDelegate>();
    auto fileLoader = std::make_shared<Knights::CPlainFileLoader>();
    auto game = std::make_shared<Knights::CGame>( fileLoader, std::make_shared<Knights::CConsoleRenderer>(), delegate );

    auto onLevelLoaded = [&]() {
        if ( game->getLevelNumber() >= LEVEL_LIMIT ) {
            game->setIsPlaying( false );
            printf("\n%s\n", Knights::fileFromString("res/outro").c_str());
            exit(0);
        }
    };

    delegate->setOnLevelLoadedCallback(onLevelLoaded );

    while ( game->isPlaying() ) {
        game->tick();
    }

  return 0;
}
