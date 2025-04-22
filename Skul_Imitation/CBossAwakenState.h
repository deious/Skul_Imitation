#pragma once
#include "IState.h"
#include "CAttackCollider.h"

class CBoss;

class CBossAwakenState : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;

    EBossStateType GetType();

private:
    float m_fElapsed = 0.f;
    bool m_bAttacked = false;
};