#ifndef CGAME_H
#define CGAME_H

namespace Knights {
  class CGame {
    std::shared_ptr<CBullKnight> bull;
    std::shared_ptr<CFalconKnight> falcon;
    std::shared_ptr<CTurtleKnight> turtle;
  public:
    CGame( std::string mapData, std::shared_ptr<IRenderer> renderer );
      void endOfTurn(std::shared_ptr<CMap> map);
  };
}
#endif
