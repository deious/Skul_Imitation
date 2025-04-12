#pragma once
#include "pch.h"
#include "Define.h"
#include "CState.h"

class CPlayer;

class CSkillState : public CState
{
public:
    CSkillState(ESkillType eType);
    void Enter(CPlayer* pPlayer) override;
    void Update(CPlayer* pPlayer) override;
    void Exit(CPlayer* pPlayer) override;
    EPlayerState GetStateID() const override;

private:
    ESkillType m_eType;
    DWORD m_dwStartTime = 0;
};

