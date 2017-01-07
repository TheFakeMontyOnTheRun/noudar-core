#ifndef NOUDAR_CORE_IRENDERER_H
#define NOUDAR_CORE_IRENDERER_H
namespace Knights {
  class IRenderer {
  public:
    virtual void drawMap( CMap &map, std::shared_ptr<CActor> current ) = 0;
    virtual char getInput() = 0;
  };
}
#endif
