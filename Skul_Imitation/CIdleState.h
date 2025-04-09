#pragma once
#include "CState.h"
class CIdleState : public CState
{
public:
	void Enter(CPlayer* pPlayer) override;
	void Update(CPlayer* pPlayer) override;
	void Exit(CPlayer* pPlayer) override;
	EPlayerState GetStateID() const override;
};

