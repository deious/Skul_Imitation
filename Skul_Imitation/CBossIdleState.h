#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossIdleState : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
};

