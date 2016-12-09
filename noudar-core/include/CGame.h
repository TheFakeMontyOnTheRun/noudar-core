#ifndef CGAME_H
#define CGAME_H

namespace Knights {

    const static char kMovePlayerNorthCommand = 'w';
    const static char kMovePlayerEastCommand = 's';
    const static char kMovePlayerSouthCommand = 'z';
    const static char kMovePlayerWestCommand = 'a';

    const static char kMovePlayerForwardCommand = 'o';
    const static char kTurnPlayerLeftCommand = 'i';
    const static char kTurnPlayerRightCommand = 'p';

    const static char kTurnPlayerNorthCommand = 'r';
    const static char kTurnPlayerEastCommand = 'f';
    const static char kTurnPlayerSouthCommand = 'c';
    const static char kTurnPlayerWestCommand = 'd';

    const static char kCastMagickForwardCommand = 'k';
    const static char kActorMeleeAttackCommand = 'e';

    const static char kGoToFirstLevelCommand = '1';
    const static char kGoToTitleLevelCommand = '0';

    const static char kEndTurnCommand = 't';
    const static char kQuitGameCommand = 'q';


  class CGame : public std::enable_shared_from_this<CGame> {
      std::shared_ptr<CMap> mMap;
      std::shared_ptr<IRenderer> mRenderer;
      std::shared_ptr<CGameDelegate> mGameDelegate;
	  std::shared_ptr<IFileLoaderDelegate> mFileLoaderDelegate;

      bool mIsPlaying;
      int mTurn = 0;
	  int mLevel = 0;
  public:
    CGame( std::shared_ptr<IFileLoaderDelegate> fileLoaderDelegate, std::shared_ptr<IRenderer> aRenderer, std::shared_ptr<CGameDelegate> aGameDelegate );
      ~CGame() = default;
      void endOfTurn(std::shared_ptr<CMap> map);
      std::shared_ptr<CMap> getMap();
      void tick();
      int getTurn();
	  void proceedToNextLevel();
	  void playLevel( int level );
      bool isPlaying();
      Vec2i getCursorPosition();
  };
}
#endif
