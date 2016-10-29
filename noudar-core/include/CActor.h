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

    enum class ETeam {
        kHeroes,
        kVillains
    };

    std::ostream& operator<<(std::ostream& os, const ETeam & aDirection );
    std::string to_string( const ETeam & aDirection );

    enum class EDirection {
        kNorth,
        kEast,
        kSouth,
        kWest
    };

    std::ostream& operator<<(std::ostream& os, const EDirection& aDirection );
    std::string to_string( const EDirection& aDirection );

    class CMap;

    class CActor {
    protected:
        EStance mStance;
        EDirection mDirection;
        ETeam mTeam;
        int mHP;
        int mDefence;
        int mAttack;
        int mRemainingAP;
        int mDefaultAP;
        int mId;
        char mView;
        std::string mName;
        Vec2i mPosition;
    public:
        void performAttack( std::shared_ptr<CActor> other);
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

        int getId();
        int getHP();
        int getAP();
        int getDefense();
        int getAttack();

        ETeam getTeam();
        EDirection getDirection();
        void setDirection( EDirection d );
        virtual void update( std::shared_ptr<CMap> map ) {}
        virtual void endOfTurn();
        std::string getName();
        virtual ~CActor() = default;
    };
}
#endif
