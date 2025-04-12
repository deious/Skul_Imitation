#include "pch.h"
#include "CSkillState.h"
#include "CIdleState.h"
#include "CPlayer.h"

CSkillState::CSkillState(ESkillType eType) : m_eType(eType) {}

void CSkillState::Enter(CPlayer* pPlayer)
{
    if (!pPlayer->Get_Skul())
        return;

    if (m_eType == ESkillType::SkillA)
        pPlayer->Get_Skul()->UseSkillA(pPlayer);
    else if (m_eType == ESkillType::SkillS)
        pPlayer->Get_Skul()->UseSkillS(pPlayer);
    else if (m_eType == ESkillType::SkillD)
        pPlayer->Get_Skul()->UseSkillD(pPlayer);
    m_dwStartTime = GetTickCount64();
}

void CSkillState::Update(CPlayer* pPlayer)
{
    pPlayer->Move_Frame();
    //if (GetTickCount64() - m_dwStartTime > 300) // 애니 끝나면 복귀
    //    pPlayer->ChangeState(new CIdleState());

    if (pPlayer->Get_CurFrame() >= pPlayer->Get_EndFrame())
        pPlayer->ChangeState(new CIdleState());
}

EPlayerState CSkillState::GetStateID() const { return EPlayerState::USESKILL; }

void CSkillState::Exit(CPlayer* pPlayer) {}
