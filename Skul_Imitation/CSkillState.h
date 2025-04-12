#pragma once
#include "CState.h"

class CPlayer;

enum class ESkillType
{
    SkillA,
    SkillS
};

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

