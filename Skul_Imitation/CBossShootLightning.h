#pragma once
#include "CBossAttackState.h"
class CBossShootLightning : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
};

