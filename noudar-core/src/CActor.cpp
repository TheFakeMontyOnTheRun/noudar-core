#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include "Vec2i.h"
#include "CActor.h"

namespace Knights {
    CActor::CActor(int aId, int defaultAP) :
            mId( aId ),
            mDefaultAP(defaultAP),
            mRemainingAP(defaultAP),
            mStance(EStance::kStanding),
            mAttack(0),
            mDefence(0),
            mHP(0),
            mDirection(EDirection::kNorth) {
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
    }

    void CActor::onAttack() {
        --mRemainingAP;
    }

    void CActor::turnLeft() {

        if ( mDirection == EDirection::kNorth ) {
            mDirection = EDirection::kWest;
        } else {
            mDirection = static_cast<EDirection>( static_cast<int>(mDirection) - 1);
        }
    }

    void CActor::turnRight() {
        if ( mDirection == EDirection::kWest ) {
            mDirection = EDirection::kNorth;
        } else {
            mDirection = static_cast<EDirection>( static_cast<int>(mDirection) + 1);
        }
    }

    void CActor::endOfTurn() {
        mRemainingAP = mDefaultAP;
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

    ETeam CActor::getTeam() {
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

    void CActor::setDirection( EDirection d ) {
        mDirection = d;
    }

    std::string CActor::getName() {
        return mName;
    }

    std::ostream& operator<<(std::ostream& os, const EDirection& aDirection ) {
        os << to_string(aDirection);

        return os;
    }

    std::string to_string( const EDirection& aDirection ) {
        switch (aDirection ) {
            case EDirection::kNorth:
                return "North";
            case EDirection::kWest:
                return "West";
            case EDirection::kSouth:
                return "South";
            case EDirection::kEast:
                return "East";
        }
    }

    EDirection wrapDirection( EDirection direction, int offset ) {
        int index = static_cast<int>(direction) + offset;

        while ( index < 0 ) {
            index += 4;
        }

        while ( index >= 4 ) {
            index -= 4;
        }

        return static_cast<EDirection>( index );
    }

    std::ostream& operator<<(std::ostream& os, const EStance& aStance ) {
        os << to_string(aStance);

        return os;
    }

    std::string to_string( const EStance& aStance) {
        switch (aStance) {
            case EStance::kAttacking:
                return "Attacking";
            case EStance::kStanding:
                return "Standidng";
            case EStance::kDead:
                return "Dead";
        }
    }


    std::ostream& operator<<(std::ostream& os, const ETeam& aTeam) {
        os << to_string(aTeam);

        return os;
    }

    std::string to_string( const ETeam& aTeam ) {
        switch (aTeam) {
            case ETeam::kHeroes:
                return "Heroes";
            case ETeam::kVillains:
                return "Villains";
        }
    }

}
