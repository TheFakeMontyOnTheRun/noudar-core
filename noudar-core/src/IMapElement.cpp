#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Vec2i.h"
#include "IMapElement.h"

namespace Knights {
    IMapElement::IMapElement() :
            mIsBlocker(false),
            mView(kEmptySpace) {
    }

    bool IMapElement::isBlocker() {
        return mIsBlocker;
    }

    char IMapElement::getView() {
        return mView;
    }
}
