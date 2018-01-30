//
// Created by monty on 13/02/17.
//

#ifndef NOUDAR_CORE_CSUGGESTITEMCOMMAND_H
#define NOUDAR_CORE_CSUGGESTITEMCOMMAND_H

namespace Knights {
	class CSuggestItemCommand : public IGameCommand {

		std::shared_ptr<CActor> mActor;
        ElementView mItemView;
	public:
        CSuggestItemCommand(std::shared_ptr<CGame> aGame,
		                 std::shared_ptr<CActor> aActor,
						 ElementView itemView
		);

		virtual std::string to_string() const override;

		virtual bool shouldEndTurn() override;

		virtual void execute() override;
	};
}

#endif //NOUDAR_CORE_CSUGGESTITEMCOMMAND_H
