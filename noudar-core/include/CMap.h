#ifndef NOUDAR_CORE_CMAP_H
#define NOUDAR_CORE_CMAP_H

namespace Knights {

	const static int kMapSize = 20;

    class CMap {
    public:

    private:

        std::shared_ptr<IMapElement> map[ kMapSize ][ kMapSize ];
        std::shared_ptr<CActor> mActors[ kMapSize ][ kMapSize ];
        std::shared_ptr<CGameDelegate> mGameDelegate;
        bool block[ kMapSize ][ kMapSize ];
        char mElement[ kMapSize ][ kMapSize ];
        std::vector<std::shared_ptr<CActor>> actors;
        std::shared_ptr<CActor> mAvatar;

    public:

        bool isValid( int x, int y );
        bool isBlockAt( int x, int y );
        CMap( const std::string& data, std::shared_ptr<CGameDelegate> aGameDelegate );
        void move( EDirection d, std::shared_ptr<CActor> a );
        bool attackIfNotFriendly( EDirection d, std::shared_ptr<CActor> a, bool mutual );
        void endOfTurn();
	    bool isLevelFinished();
        Vec2i getActorTargetPosition( std::shared_ptr<CActor> a );
        std::shared_ptr<IMapElement> getMapElement( Vec2i position );
        char getElementAt( int x, int y );
        std::shared_ptr<CActor> getAvatar();
        std::vector<std::shared_ptr<CActor>> getActors();
        std::shared_ptr<CActor> getActorAt( Vec2i position );
        void setActorAt( Vec2i position, std::shared_ptr<CActor> actor );
        void moveActor( Vec2i from, Vec2i to, std::shared_ptr<CActor> actor );
        std::shared_ptr<CActor> attack( std::shared_ptr<CActor> a, Vec2i position , bool mutual );
    };
}
#endif
