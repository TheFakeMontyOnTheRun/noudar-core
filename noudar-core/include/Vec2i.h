//
// Created by monty on 05/10/16.
//

#ifndef NOUDAR_CORE_VEC2I_H
#define NOUDAR_CORE_VEC2I_H
namespace Knights {

    class Vec2i {
    public:
        int x = 0;
        int y = 0;

        Vec2i( int aX, int aY ) {
            x = aX;
            y = aY;
        }

        Vec2i() { x = y = 0; }

        bool operator==( const Vec2i &other ) {
            return this->x == other.x && this->y == other.y;
        }
    };

    enum class EDirection {
        kNorth,
        kEast,
        kSouth,
        kWest
    };

    std::ostream& operator<<(std::ostream& os, const EDirection& aDirection );
    std::string to_string( const EDirection& aDirection );
    EDirection wrapDirection( EDirection direction, int offset );
    Vec2i mapOffsetForDirerction( EDirection direction );

}
#endif //KNIGHTS_IN_PORTO_VEC2I_H
