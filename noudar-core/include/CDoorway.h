#ifndef NOUDAR_CORE_CDOORWAY_H
#define NOUDAR_CORE_CDOORWAY_H
namespace Knights {
    enum EDoorwayFunction {
        kEntry,
        kExit
    };

    class CDoorway : public IMapElement {
        const EDoorwayFunction doorFunction;
    public:
        CDoorway( EDoorwayFunction doorFunction );
        const EDoorwayFunction getDoorFunction();
    };
}
#endif
