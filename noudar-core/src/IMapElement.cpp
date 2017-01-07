#include "Vec2i.h"
#include "IMapElement.h"

namespace Knights {
    IMapElement::IMapElement() :
            mIsBlocker(false),
            mView(kEmptySpace),
            mPosition(0, 0) {
    }

    Vec2i IMapElement::getPosition() {
        return mPosition;
    }

    bool IMapElement::isBlocker() {
        return mIsBlocker;
    }

    char IMapElement::getView() {
        return mView;
    }
}
