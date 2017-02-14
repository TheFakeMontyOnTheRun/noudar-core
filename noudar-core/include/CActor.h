// CActor - a generic abstract Actor
// 2016 - Daniel Monteiro
//
#ifndef NOUDAR_CORE_CACTOR_H
#define NOUDAR_CORE_CACTOR_H

namespace Knights {

	enum class EStance {
		kStanding,
		kAttacking,
		kDead
	};

	std::ostream &operator<<(std::ostream &os, const EStance &aStance);

	std::string to_string(const EStance &aStance);

	class CMap;

	class CActor {
	protected:
		EStance mStance;
		EDirection mDirection;
		int mId;
		int mMoves;
		int mDefaultAP;
		int mRemainingAP;
		int mAttack;
		int mDefence;
		int mHP;
		Vec2i mPosition;
		char mView;
		std::string mName;
		std::shared_ptr<CTeam> mTeam;
		std::vector<std::shared_ptr<CItem>> mInventory;
		std::shared_ptr<CItem> mCurrentItem;

	public:
		virtual void performAttack(std::shared_ptr<CActor> other);

		CActor(int aId, int defaultAP);

		Vec2i getPosition();

		void setPosition(Vec2i position);

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

		int getMoves();

		int getHP();

		int getAP();

		int getDefense();

		int getAttack();

		void addHP(int aHP);

		void useCurrentItem();

		std::shared_ptr<CTeam> getTeam();

		EDirection getDirection();

		EStance getStance();

		void setDirection(EDirection d);

		virtual void update(std::shared_ptr<CMap> map) {}

		virtual void endOfTurn();

		std::string getName();

		virtual ~CActor() = default;

		void selectNextItem();

		void selectPreviousItem();

		std::shared_ptr<CItem> getSelectedItem();

		void giveItem( std::shared_ptr<CItem> aItem );

		std::shared_ptr<CItem> removeItemFromInventory( std::shared_ptr<CItem> itemToRemove );
	};
}
#endif
