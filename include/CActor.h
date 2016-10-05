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

    enum class ETeam {
        kHeroes,
        kVillains
    };

    enum class EDirection {
        kNorth,
        kEast,
        kSouth,
        kWest
    };

    class CActor : public IMapElement {
    public:
        EStance mStance;
        EDirection mDirection;
        ETeam mTeam;
        int mHP;
        int mDefence;
        int mAttack;
        int mRemainingAP;
        int mDefaultAP;
        int mId;
    public:
        void performAttack( std::shared_ptr<CActor> other);
        CActor( int aId, int defaultAP );
        void onMove();
        void onAttack();
        bool canMove();
        bool canAttack();
        bool hasEnoughAP();
        void turnLeft();
        void turnRight();
        virtual void endOfTurn();
    };
}
#endif
