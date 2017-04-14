#ifndef NOUDAR_CORE_IMAPELEMENT_H
#define NOUDAR_CORE_IMAPELEMENT_H
namespace Knights {
    const char kEmptySpace = '.';
    class IMapElement {
    public:
        char mView = kEmptySpace;
    public:
        char getView();
    };
}
#endif
