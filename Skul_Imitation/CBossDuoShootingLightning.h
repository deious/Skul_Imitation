#pragma once
#include "IState.h"
#include "CBoss.h"

class CBossDuoShootingLightning : public IState<CBoss>
{
public:
    void Enter(CBoss* pBoss) override;
    void Update(CBoss* pBoss) override;
    void Exit(CBoss* pBoss) override;
};

