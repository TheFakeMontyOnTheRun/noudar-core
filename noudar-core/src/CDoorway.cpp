#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Vec2i.h"
#include "IMapElement.h"
#include "CDoorway.h"

namespace Knights {

    CDoorway::CDoorway(EDoorwayFunction f) : doorFunction(f) {
        if (f == EDoorwayFunction::kExit) {
            mView = 'E';
        } else {
            mView = 'B';
        }
    }

    const EDoorwayFunction CDoorway::getDoorFunction() {
        return doorFunction;
    }
}