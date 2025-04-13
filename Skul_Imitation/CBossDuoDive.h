#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossDuoDive : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;

private:
    bool m_bDived = false;
    float m_fWaitTime = 0.f;
    float m_fDiveSpeed = 25.f;
    float m_fTargetY = 400.f;
};

