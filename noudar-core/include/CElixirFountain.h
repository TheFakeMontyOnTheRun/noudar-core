//
// Created by monty on 31/12/16.
//

#ifndef NOUDAR_CORE_CELIXIRFOUNTAIN_H
#define NOUDAR_CORE_CELIXIRFOUNTAIN_H

namespace Knights {
	class CElixirFountain: public CActor {
	public:
		explicit CElixirFountain(int aId);
		void performAttack( std::shared_ptr<CActor> other) override;
	};
}


#endif //NOUDAR_CORE_CELIXIRFOUNTAIN_H
