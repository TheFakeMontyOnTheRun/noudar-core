#ifndef NOUDAR_CORE_IMAPELEMENT_H
#define NOUDAR_CORE_IMAPELEMENT_H
namespace Knights {
    const char kEmptySpace = '.';
    class IMapElement {
    public:
        bool mIsBlocker;

        char mView;
    public:
        Vec2i mPosition;
        Vec2i getPosition();
        bool isBlocker();
        char getView();
        IMapElement();
        virtual ~IMapElement() = default;
    };
}
#endif
