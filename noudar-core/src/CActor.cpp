#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Vec2i.h"
#include "CTeam.h"
#include "CActor.h"

namespace Knights {
    CActor::CActor(int aId, int defaultAP) :
            mStance(EStance::kStanding),
            mDirection(EDirection::kNorth),
            mId(aId),
            mMoves(0),
            mDefaultAP(defaultAP),
            mRemainingAP(defaultAP),
            mAttack(0),
            mDefence(0),
            mHP(0) {
    }

    bool CActor::canMove() {
        return hasEnoughAP();
    }

    bool CActor::canAttack() {
        return hasEnoughAP();
    }

    bool CActor::hasEnoughAP() {
        return mRemainingAP > 0;
    }

    void CActor::onMove() {
        --mRemainingAP;
        ++mMoves;
	    mStance = EStance::kAttacking;
    }

    void CActor::onAttack() {
        --mRemainingAP;
    }

    void CActor::turnLeft() {

        if (mDirection == EDirection::kNorth) {
            mDirection = EDirection::kWest;
        } else {
            mDirection = static_cast<EDirection>( static_cast<int>(mDirection) - 1);
        }
    }

    void CActor::turnRight() {
        if (mDirection == EDirection::kWest) {
            mDirection = EDirection::kNorth;
        } else {
            mDirection = static_cast<EDirection>( static_cast<int>(mDirection) + 1);
        }
    }

    void CActor::endOfTurn() {
        mRemainingAP = mDefaultAP;
	    mStance = EStance::kStanding;
    }

    void CActor::performAttack(std::shared_ptr<CActor> other) {

        onAttack();
        int diff = (mAttack - other->mDefence);

        if (diff > 0) {
            other->mHP -= diff;
        }
    }

    Vec2i CActor::getPosition() {
        return mPosition;
    }

    void CActor::setPosition(Vec2i position) {
        mPosition = position;
    }

    std::shared_ptr<CTeam> CActor::getTeam() {
        return mTeam;
    }

    bool CActor::isAlive() {
        return mHP > 0;
    }

    EDirection CActor::getDirection() {
        return mDirection;
    }

    int CActor::getHP() {
        return mHP;
    }

    int CActor::getAP() {
        return mRemainingAP;
    }

    int CActor::getDefense() {
        return mDefence;
    }

    int CActor::getAttack() {
        return mAttack;
    }

    int CActor::getId() {
        return mId;
    }

    void CActor::setDirection(EDirection d) {
        mDirection = d;
    }

    std::string CActor::getName() {
        return mName;
    }

    char CActor::getView() {
        return mView;
    }

    int CActor::getMoves() {
        return mMoves;
    }


	void CActor::addHP(int aHP ) {
		mHP += aHP;
	}

    EStance CActor::getStance() {
        return mStance;
    }

    std::ostream& operator<<(std::ostream& os, const EStance& aStance ) {
        os << to_string(aStance);

        return os;
    }

    std::string to_string(const EStance &aStance) {
        switch (aStance) {
            case EStance::kAttacking:
                return "Attacking";
            case EStance::kStanding:
                return "Standidng";
            case EStance::kDead:
                return "Dead";
        }
    }
}
