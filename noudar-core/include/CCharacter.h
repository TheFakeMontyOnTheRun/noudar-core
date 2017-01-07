#ifndef NOUDAR_CORE_CCHARACTER_H
#define NOUDAR_CORE_CCHARACTER_H

namespace Knights {

    class CCharacter: public CActor {
    public:
        CCharacter( std::shared_ptr<CCharacterArchetype> aArchetype, std::shared_ptr<CTeam> aTeam, int aId);
    };
}
#endif
