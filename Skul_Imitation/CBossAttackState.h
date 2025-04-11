#pragma once
#pragma once
#include "IState.h"
#include "CAttackCollider.h"

class CBoss;

class CBossAttackState : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;

private:
    float m_fElapsed = 0.f;
    bool m_bAttacked = false;
};
