#ifndef NOUDAR_CORE_CMONSTER_H
#define NOUDAR_CORE_CMONSTER_H
namespace Knights {

    class CMap;

    class CMonster : public CCharacter {
    public:
        CMonster( std::shared_ptr<CCharacterArchetype> aArchetype, std::shared_ptr<CTeam> aTeam, int aId);

        void update(std::shared_ptr <CMap> map) override;

        bool actOn(int newX, int newY, std::shared_ptr <CMap> map);

        bool dealWith( std::shared_ptr<CMap> map, int x, int y );
    };
}
#endif
