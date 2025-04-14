#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossDuoShootingLightning : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
    EBossStateType GetType() override;

private:
    float m_fElapsed = 0.f;
    int m_iPhase = 0;
    std::vector<Vec2> m_Offsets;
};

