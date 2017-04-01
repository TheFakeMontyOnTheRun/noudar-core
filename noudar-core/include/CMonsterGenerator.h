#ifndef NOUDAR_CORE_CMONSTERGENERATOR_H
#define NOUDAR_CORE_CMONSTERGENERATOR_H

namespace Knights {
    class CMonsterGenerator : public CActor {
    public:
        CMonsterGenerator(int aId, int aliveForTurns);

        void update(std::shared_ptr<CMap> map) override;
    };
}
#endif
