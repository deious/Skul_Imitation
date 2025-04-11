#pragma once
#include "CState.h"

class CAttackState : public CState
{
public:
    CAttackState(int iCombo = 0);

public:
    void Enter(CPlayer* pPlayer) override;
    void Update(CPlayer* pPlayer) override;
    void Exit(CPlayer* pPlayer) override;

private:
    DWORD m_dwStartTime = 0;
    bool m_bAnimEnd = false;

    // CState을(를) 통해 상속됨
    EPlayerState GetStateID() const override;

private:
    int m_iCombo = 0;
    bool m_bQueued = false;
    bool m_bColliderSpawned = false;
    ULONGLONG m_dwLastAttackTime = 0;
    const DWORD COMBO_DELAY = 1000; // 콤보 허용 시간(ms)
};

