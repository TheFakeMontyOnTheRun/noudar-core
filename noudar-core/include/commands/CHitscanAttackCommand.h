//
// Created by monty on 30/01/17.
//

#ifndef NOUDAR_CORE_CHITSCANATTACKCOMMAND_H
#define NOUDAR_CORE_CHITSCANATTACKCOMMAND_H

namespace Knights {
	class CHitscanAttackCommand  : public IGameCommand {
		std::shared_ptr<CActor> mAttacker;
	public:
		CHitscanAttackCommand( std::shared_ptr<CGame> aGame, std::shared_ptr<CActor> aAttacker );
		virtual std::string to_string() const override;
		virtual bool shouldEndTurn() override;
		virtual void execute() override;
	};
}

#endif //NOUDAR_CORE_CHITSCANATTACKCOMMAND_H
