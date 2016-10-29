//
// Created by monty on 25/10/16.
//

#ifndef NOUDAR_CORE_COMMANDS_CMOVEACTORCOMMAND_H
#define NOUDAR_CORE_COMMANDS_CMOVEACTORCOMMAND_H

namespace Knights {
    class CMoveActorCommand : public IGameCommand {
        EDirection mDirection;
    public:
        CMoveActorCommand( EDirection direction  );
        virtual std::string to_string() const override;
        virtual bool shouldEndTurn() override;
        virtual void execute() override;
    };
}

#endif //NOUDAR_CORE_ACTORMELEEATTACKACTION_H
