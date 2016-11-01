//
// Created by monty on 25/10/16.
//

#ifndef NOUDAR_CORE_COMMANDS_CACTORMELEEATTACKACTION_H
#define NOUDAR_CORE_COMMANDS_CACTORMELEEATTACKACTION_H

namespace Knights {
    class CActorMeleeAttackCommand : public IGameCommand {
        std::shared_ptr<CActor> mTarget;
        std::shared_ptr<CActor> mAttacker;
    public:
        CActorMeleeAttackCommand( std::shared_ptr<CGame> aGame, std::shared_ptr<CActor> aAttacker, std::shared_ptr<CActor> aTarget );
        virtual std::string to_string() const override;
        virtual bool shouldEndTurn() override;
        virtual void execute() override;
    };
}

#endif //NOUDAR_CORE_ACTORMELEEATTACKACTION_H
