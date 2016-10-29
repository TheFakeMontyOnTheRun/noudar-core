#ifndef knights2_CBullKnight_H
#define knights2_CBullKnight_H
namespace Knights {
    class CKnight : public CActor {
    public:
        CKnight(int aId);
        void update(std::shared_ptr <CMap> map) override;
    };
}
#endif
