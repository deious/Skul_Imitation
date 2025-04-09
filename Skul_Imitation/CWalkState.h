#pragma once
#include "CState.h"

class CWalkState : public CState
{
public:
    void Enter(CPlayer* pPlayer) override;
    void Update(CPlayer* pPlayer) override;
    void Exit(CPlayer* pPlayer) override;

    // CState을(를) 통해 상속됨
    EPlayerState GetStateID() const override;
};

