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
#include "CActor.h"
#include "CGameDelegate.h"
#include "CMap.h"
#include "IRenderer.h"
#include "CConsoleRenderer.h"
#include "CKnight.h"
#include "CEditor.h"


int main ( int argc, char **argv ) {


	auto fileLoader = std::make_shared<Knights::CPlainFileLoader>();
    auto editor = std::make_shared<Knights::CEditor>( fileLoader, std::make_shared<Knights::CConsoleRenderer>());

    while ( true ) {
        editor->tick();
    }

  return 0;
}
