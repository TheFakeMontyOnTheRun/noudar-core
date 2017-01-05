// CActor - a generic abstract Actor
// 2016 - Daniel Monteiro
//
#ifndef knights2_CActor_H
#define knights2_CActor_H

namespace Knights {

    enum class EStance {
        kStanding,
        kAttacking,
        kDead
    };

    std::ostream& operator<<(std::ostream& os, const EStance & aDirection );
    std::string to_string( const EStance & aDirection );

    enum class EDirection {
        kNorth,
        kEast,
        kSouth,
        kWest
    };

    std::ostream& operator<<(std::ostream& os, const EDirection& aDirection );
    std::string to_string( const EDirection& aDirection );
    EDirection wrapDirection( EDirection direction, int offset );

    class CMap;

    class CActor {
    protected:
        EStance mStance;
        EDirection mDirection;
        int mId;
        int mDefaultAP;
        int mRemainingAP;
        int mAttack;
        int mDefence;
        int mHP;
        Vec2i mPosition;
		char mView;
		std::string mName;
		std::shared_ptr<CTeam> mTeam;
    public:
        virtual void performAttack( std::shared_ptr<CActor> other);
        CActor( int aId, int defaultAP );
        Vec2i getPosition();
        void setPosition( Vec2i position );
        void onMove();
        void onAttack();
        bool canMove();
        bool canAttack();
        bool hasEnoughAP();
        bool isAlive();
        void turnLeft();
        void turnRight();
		char getView();
        int getId();
        int getHP();
        int getAP();
        int getDefense();
        int getAttack();

        std::shared_ptr<CTeam> getTeam();
        EDirection getDirection();
        void setDirection( EDirection d );
        virtual void update( std::shared_ptr<CMap> map ) {}
        virtual void endOfTurn();
        std::string getName();
        virtual ~CActor() = default;
    };
}
#endif
