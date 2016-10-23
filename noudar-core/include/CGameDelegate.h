//
// Created by monty on 22/10/16.
//

#ifndef DUNGEONSOFNOUDAR_NDK_CGAMEDELEGATE_H
#define DUNGEONSOFNOUDAR_NDK_CGAMEDELEGATE_H

namespace Knights {
	class CGameDelegate {

	public:

		CGameDelegate();

		void setMonsterDiedCallback(std::function<void(Knights::Vec2i)> aCallback);

		void setPlayerDiedCallback(std::function<void(Knights::Vec2i)> aCallback);

		void setMonsterAttackedCallback(std::function<void(Knights::Vec2i)> aCallback);

		void setPlayerAttackedCallback(std::function<void(Knights::Vec2i)> aCallback);

		void setPlayerDamagedCallback(std::function<void(Knights::Vec2i)> aCallback);

		void setMonsterDamagedCallback(std::function<void(Knights::Vec2i)> aCallback);

		void onPlayerAttacked(Knights::Vec2i);

		void onMonsterAttacked(Knights::Vec2i);

		void onPlayerDied(Knights::Vec2i);

		void onMonsterDied(Knights::Vec2i);

		void onMonsterDamaged(Knights::Vec2i);

		void onPlayerDamaged(Knights::Vec2i);

	private:
		std::function<void(Knights::Vec2i)> mOnMonsterDead;

		std::function<void(Knights::Vec2i)> mOnPlayerDead;

		std::function<void(Knights::Vec2i)> mOnPlayerAttack;

		std::function<void(Knights::Vec2i)> mOnMonsterAttack;

		std::function<void(Knights::Vec2i)> mOnMonsterDamaged;

		std::function<void(Knights::Vec2i)> mOnPlayerDamaged;
	};
}

#endif //DUNGEONSOFNOUDAR_NDK_CGAMEDELEGATE_H
