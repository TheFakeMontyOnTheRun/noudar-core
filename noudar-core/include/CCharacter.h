#ifndef NOUDAR_CORE_CCHARACTER_H
#define NOUDAR_CORE_CCHARACTER_H

namespace Knights {
    class CCharacter;

    using CUpdateMethod = std::function<void(std::shared_ptr<CActor>, std::shared_ptr<CMap>)>;

    static const CUpdateMethod kEmptyUpdateMethod = [](std::shared_ptr<CActor>, std::shared_ptr<CMap>){};

    class CCharacter: public CActor {

        CUpdateMethod mUpdateMethod;
        CCharacterArchetype mArchetype;
    public:
        CCharacter( std::shared_ptr<CCharacterArchetype> aArchetype, ETeam aTeam, ActorId aId, CUpdateMethod aUpdateMethod = kEmptyUpdateMethod);
        virtual void update(std::shared_ptr<CMap> map) override;
        CCharacterArchetype getArchetype();
        virtual ~CCharacter();
    };
}
#endif
