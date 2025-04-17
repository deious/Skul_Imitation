#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossDuoDive : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
    EBossStateType GetType() override;

private:
    bool m_bDived = false;
    float m_fWaitTime = 0.f;
    float m_fDiveSpeed = 25.f;
    float m_fTargetY = 400.f;
    wstring m_sEffectKey;
    EffectInfo m_tEffectInfo;
};

