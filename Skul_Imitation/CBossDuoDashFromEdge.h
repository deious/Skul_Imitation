#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossDuoDashFromEdge : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
    EBossStateType GetType() override;

private:
    float m_fWaitTime = 0.f;
    bool m_bDashed = false;
    float m_fDashSpeed = 700.f;
    float m_fDashTime = 2.f;
    wstring m_sEffectKey;
    EffectInfo m_tEffect;
};

