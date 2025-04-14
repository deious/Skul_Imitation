#pragma once
#include "CBoss.h"

extern bool g_bIsTeamPatternTime;

class CBossWaitState : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
    EBossStateType GetType() override;
};

