//
// Created by monty on 03/01/17.
//

#ifndef NOUDAR_CORE_CMONSTERARCHETYPE_H
#define NOUDAR_CORE_CMONSTERARCHETYPE_H

namespace Knights {
	class CCharacterArchetype {
		int mAttack;
		int mDefense;
		int mHP;
		int mAP;
		char mView;
		std::string mName;

	public:
		CCharacterArchetype( int aAttack, int aDefense, int aHP, int aAP, char aView, std::string aName );
		int getAttack();
		int getDefense();
		int getHP();
		int getAP();
		char getView();
		std::string getName();
	};
}

#endif //NOUDAR_CORE_CMONSTERARCHETYPE_H
