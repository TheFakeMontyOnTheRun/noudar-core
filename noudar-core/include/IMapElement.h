#ifndef NOUDAR_CORE_IMAPELEMENT_H
#define NOUDAR_CORE_IMAPELEMENT_H
namespace Knights {
    const char kEmptySpace = '.';
    class IMapElement {
    public:
        bool mIsBlocker;

        char mView;
    public:
        bool isBlocker();
        char getView();
        IMapElement();
        virtual ~IMapElement() = default;
    };
}
#endif
