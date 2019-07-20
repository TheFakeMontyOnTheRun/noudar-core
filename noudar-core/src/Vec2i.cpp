#include <stdint.h>
#include "Vec2i.h"

namespace Knights {

    Vec2i::Vec2i(int aX, int aY) : x(aX), y(aY) {
    }

    Vec2i::Vec2i() : x(0), y(0) {
    }

    bool operator==(const Vec2i &lh, const Vec2i &rh) {
        return (lh.x == rh.x) && (lh.y == rh.y);
    }

    bool operator!=(const Vec2i &lh, const Vec2i &rh) {
        return (lh.x != rh.x) || (lh.y != rh.y);
    }

    Vec2i &Vec2i::operator+=(const Vec2i &other) {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vec2i &Vec2i::operator-=(const Vec2i &other) {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    Vec2i mapOffsetForDirection(EDirection aDirection) {
        switch (aDirection) {
            case EDirection::kEast:
                return {1, 0};
            case EDirection::kWest:
                return {-1, 0};
            case EDirection::kSouth:
                return {0, 1};
            case EDirection::kNorth:
            default:
                return {0, -1};
        }
    }

    EDirection wrapDirection(EDirection direction, int offset) {
        int index = static_cast<int>(direction) + offset;

        while (index < 0) {
            index += 4;
        }

        while (index >= 4) {
            index -= 4;
        }

        return static_cast<EDirection>( index );
    }

    EDirection oppositeOf(Knights::EDirection d) {
        switch (d) {
            case Knights::EDirection::kSouth:
                return Knights::EDirection::kNorth;
            case Knights::EDirection::kEast:
                return Knights::EDirection::kWest;
            case Knights::EDirection::kWest:
                return Knights::EDirection::kEast;
            case Knights::EDirection::kNorth:
            default:
                return Knights::EDirection::kSouth;
        }
    }

    EDirection leftOf(Knights::EDirection d) {
        switch (d) {
            case Knights::EDirection::kNorth:
                return Knights::EDirection::kWest;
            case Knights::EDirection::kSouth:
                return Knights::EDirection::kEast;
            case Knights::EDirection::kEast:
                return Knights::EDirection::kNorth;
            case Knights::EDirection::kWest:
            default:
                return Knights::EDirection::kSouth;
        }
    }

    EDirection rightOf(Knights::EDirection d) {
        switch (d) {
            case Knights::EDirection::kNorth:
                return Knights::EDirection::kEast;
            case Knights::EDirection::kSouth:
                return Knights::EDirection::kWest;
            case Knights::EDirection::kEast:
                return Knights::EDirection::kSouth;
            case Knights::EDirection::kWest:
            default:
                return Knights::EDirection::kNorth;
        }
    }

    Vec2i operator+(const Vec2i &lh, const Vec2i &rh) {
        return Vec2i{static_cast<int16_t >(lh.x + rh.x), static_cast<int16_t >(lh.y + rh.y)};
    }
}
