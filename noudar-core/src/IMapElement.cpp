#include <string>
#include <memory>
#include <utility>

#include "Vec2i.h"
#include "IMapElement.h"

namespace Knights {
    ElementView IMapElement::getView() {
        return mView;
    }
}
