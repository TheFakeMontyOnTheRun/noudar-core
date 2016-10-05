#ifndef knights2_CMap_H
#define knights2_CMap_H

#include "CBullKnight.h"
#include "CFalconKnight.h"
#include "CTurtleKnight.h"

namespace Knights {
    class CMap {
    public:
        std::shared_ptr<IMapElement> map[ 20 ][ 20 ];
        bool block[ 20 ][ 20 ];
        std::vector<std::shared_ptr<CActor>> actors;

        std::shared_ptr<CBullKnight> bull;
        std::shared_ptr<CFalconKnight> falcon;
        std::shared_ptr<CTurtleKnight> turtle;
    public:
        CMap( const std::string& data );
        void move( EDirection d, std::shared_ptr<CActor> a );
        bool attackIfNotFriendly( EDirection d, std::shared_ptr<CActor> a, bool mutual );
        void endOfTurn();
        std::shared_ptr<IMapElement> getMapElement( Vec2i position );
        std::shared_ptr<CActor> attack( std::shared_ptr<CActor> a, Vec2i position , bool mutual );
    };
}
#endif
