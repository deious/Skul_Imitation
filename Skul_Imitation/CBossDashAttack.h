#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossDashAttack : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
    EBossStateType GetType() override;

private:
    bool m_bAttacked = false;
    float m_fElapsed = 0.f;
    float m_fDashSpeed = 500.f;
    float m_fDashDuration = 1.f;
    float fDirection;
};

