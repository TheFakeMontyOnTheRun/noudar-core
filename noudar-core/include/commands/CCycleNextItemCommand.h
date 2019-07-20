//
// Created by monty on 12/02/17.
//

#ifndef NOUDAR_CORE_CCYCLENEXTITEMCOMMAND_H
#define NOUDAR_CORE_CCYCLENEXTITEMCOMMAND_H

namespace Knights {
    class CCycleNextItemCommand : public IGameCommand {

        std::shared_ptr<CActor> mActor;
        std::string mItemName = "";
    public:
        CCycleNextItemCommand(std::shared_ptr<CGame> aGame, std::shared_ptr<CActor> aActor);

        virtual std::string to_string() const override;

        virtual bool shouldEndTurn() override;

        virtual void execute() override;

        virtual ~CCycleNextItemCommand() override;
    };
}

#endif //NOUDAR_CORE_CCYCLENEXTITEMCOMMAND_H
