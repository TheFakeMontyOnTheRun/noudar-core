/*
  main.c
  The Knights from Porto

  Created by Daniel Monteiro on 11/26/14.
  Copyright (c) 2016 Daniel Monteiro. All rights reserved.
*/
#ifndef CCONSOLERENDERER_H
#define CCONSOLERENDERER_H
namespace Knights {
  class CConsoleRenderer : public IRenderer {
  public:
      CConsoleRenderer();
      ~CConsoleRenderer();
    void drawMap( CMap& map, std::shared_ptr<CActor> current, int turn ) override;
    char getInput() override;
  };
}
#endif
