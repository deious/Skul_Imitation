#pragma once
#include "CState.h"
class CDashState : public CState
{
public:
	void Enter(CPlayer* pPlayer) override;
	void Update(CPlayer* pPlayer) override;
	void Exit(CPlayer* pPlayer) override;
	EPlayerState GetStateID() const override;

private:
	ULONGLONG m_dwStartTime = 0;
};

