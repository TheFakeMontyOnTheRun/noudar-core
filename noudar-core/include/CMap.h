#ifndef NOUDAR_CORE_CMAP_H
#define NOUDAR_CORE_CMAP_H

namespace Knights {

	const static int kMapSize = 40;

    class CMap {
    public:

    private:

        std::shared_ptr<IMapElement> map[ kMapSize ][ kMapSize ];
        std::shared_ptr<CActor> mActors[ kMapSize ][ kMapSize ];
        std::shared_ptr<CGameDelegate> mGameDelegate;

	    bool mBlockCharacterMovement[ kMapSize ][ kMapSize ];
        ElementView mElement[ kMapSize ][ kMapSize ];
	    std::array< std::array< std::shared_ptr<CItem>, kMapSize >, kMapSize > mItems;
        std::array< std::array< bool, kMapSize >, kMapSize > mBlockProjectiles;
        std::array< std::array< bool, kMapSize >, kMapSize > mBlockView;
        std::vector<std::shared_ptr<CActor>> actors;
        std::shared_ptr<CActor> mAvatar;
		ActorId mCurrentId = 1;

		void floodFill( Vec2i position, std::map<ElementView, ElementView> transformations );
    public:

        bool isValid( const Vec2i& p );
        bool isBlockMovementAt(const Vec2i &p);
        bool isBlockProjectilesAt( const Vec2i &p );
        bool isBlockViewAt( const Vec2i &p );
        CMap( const std::string& data, std::shared_ptr<CGameDelegate> aGameDelegate );
        void move( EDirection d, std::shared_ptr<CActor> a );
        void endOfTurn();
	    bool isLevelFinished();
        Vec2i getActorTargetPosition( std::shared_ptr<CActor> a );
		Vec2i getTargetProjection( std::shared_ptr<CActor> a );
        ElementView getElementAt( const Vec2i& p );
		ItemView getItemViewAt( const Vec2i& p );
		std::shared_ptr<CActor> getAvatar();
        std::vector<std::shared_ptr<CActor>> getActors();
        std::shared_ptr<CActor> getActorAt( Vec2i position );
        void setActorAt( Vec2i position, std::shared_ptr<CActor> actor );
		void removeActorFrom( Vec2i position );
        void moveActor( Vec2i from, Vec2i to, std::shared_ptr<CActor> actor );
        std::shared_ptr<CActor> attack( std::shared_ptr<CActor> a, Vec2i position , bool mutual );
	    Vec2i projectHitscanPosition(Vec2i position, EDirection dir);
	    void giveItemAt( Vec2i from, std::shared_ptr<CActor> to );
		std::shared_ptr<Knights::CItem> getItemAt( Vec2i from );
		void putItemAt( std::shared_ptr<CItem>, Vec2i destination );
		void addActorAt( std::shared_ptr<CActor> actor, const Vec2i& position );
		ActorId getLastestId();
		std::shared_ptr<CGameDelegate> getGameDelegate();
    };
}
#endif
