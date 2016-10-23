#ifndef CGAME_H
#define CGAME_H

namespace Knights {
  class CGame {
      std::shared_ptr<CMap> mMap;
      std::shared_ptr<IRenderer> mRenderer;
      std::shared_ptr<CGameDelegate> mGameDelegate;
      bool mIsPlaying;
      int mTurn = 0;
  public:
    CGame( std::string mapData, std::shared_ptr<IRenderer> aRenderer, std::shared_ptr<CGameDelegate> aGameDelegate );
      ~CGame() = default;
      void endOfTurn(std::shared_ptr<CMap> map);
      void tick();
      int getTurn();
      bool isPlaying();
  };
}
#endif
