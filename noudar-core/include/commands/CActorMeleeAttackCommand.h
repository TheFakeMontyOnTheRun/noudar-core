//
// Created by monty on 25/10/16.
//

#ifndef NOUDAR_CORE_COMMANDS_CACTORMELEEATTACKACTION_H
#define NOUDAR_CORE_COMMANDS_CACTORMELEEATTACKACTION_H

namespace Knights {
    class CActorMeleeAttackCommand : public IGameCommand {
        float mStrength = 0.0f;
        std::shared_ptr<CActor> mTarget;
    public:
        CActorMeleeAttackCommand( float strength, std::shared_ptr<CActor> target );
        virtual std::string to_string() const override;
        virtual bool shouldEndTurn() override;
        virtual void execute() override;
    };
}

#endif //NOUDAR_CORE_ACTORMELEEATTACKACTION_H
