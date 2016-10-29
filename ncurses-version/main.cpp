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

#include "Vec2i.h"
#include "IMapElement.h"
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CConsoleRenderer.h"
#include "CBullKnight.h"
#include "CGame.h"


std::string readMap(const char *mapName) {

    std::string entry;
    std::ifstream mapFile(mapName);

    char line[80];

    while (!mapFile.eof()) {
        mapFile >> line;
        entry += line;
    }


    auto position = entry.find('\n');

    while (position != std::string::npos) {
        entry.replace(position, 1, "");
        position = entry.find('\n', position + 1);
    }

    return entry;
}

int main ( int argc, char **argv ) {
    std::string mapData = readMap("res/map_tiles0.txt");

    auto delegate = std::make_shared<Knights::CGameDelegate>();
    Knights::CGame game( mapData, std::make_shared<Knights::CConsoleRenderer>(), delegate );

    while ( game.isPlaying() ) {
        game.tick();
    }

  return 0;
}
