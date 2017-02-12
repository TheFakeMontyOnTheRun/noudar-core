/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2014 Daniel Monteiro. All rights reserved.
*/

#include <utility>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

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


int main ( int argc, char **argv ) {


    auto delegate = std::make_shared<Knights::CGameDelegate>();
    auto fileLoader = std::make_shared<Knights::CPlainFileLoader>();
    auto game = std::make_shared<Knights::CGame>( fileLoader, std::make_shared<Knights::CConsoleRenderer>(), delegate );

    while ( game->isPlaying() ) {
        game->tick();
    }

  return 0;
}
