#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Vec2i.h"
#include "IMapElement.h"

namespace Knights {
    char IMapElement::getView() {
        return mView;
    }
}
