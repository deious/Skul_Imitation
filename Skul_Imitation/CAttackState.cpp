#include "pch.h"
#include "CAttackState.h"
#include "CPlayer.h"
#include "CIdleState.h"
#include "CKeyMgr.h"
#include "CWalkState.h"
#include "CDashState.h"
#include "CJumpStartState.h"

CAttackState::CAttackState(int iCombo) : m_iCombo(iCombo)
{
}

void CAttackState::Enter(CPlayer* pPlayer)
{
    m_dwLastAttackTime = GetTickCount64();

    switch (m_iCombo)
    {
    case 0: pPlayer->Set_Frame(0, 4, 6, 100); break; // 1타
    case 1: pPlayer->Set_Frame(0, 3, 7, 100); break; // 2타
    case 2: pPlayer->Set_Frame(0, 3, 8, 100); break; // 3타
    }
}

void CAttackState::Update(CPlayer* pPlayer)
{
    if (CKeyMgr::Get_Instance()->Key_Down('X') && !m_bQueued)
        m_bQueued = true;

    // 콤보 유지시간 초과 시 초기화
    if (GetTickCount64() - m_dwLastAttackTime > COMBO_DELAY)
    {
        pPlayer->ChangeState(new CIdleState());
        return;
    }

    if (!m_bColliderSpawned && pPlayer->Get_CurFrame() == 2)
    {
        pPlayer->Create_AttackCollider(m_iCombo);
        m_bColliderSpawned = true;
    }

    m_bAnimEnd = pPlayer->Move_Frame();

    if (m_bAnimEnd)
    {
        if (m_bQueued && m_iCombo < 2)
        {
            pPlayer->ChangeState(new CAttackState(m_iCombo + 1));
        }
        else
        {
            pPlayer->ChangeState(new CIdleState());
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
    {
        pPlayer->ChangeState(new CWalkState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('C') && !pPlayer->Get_IsJump())
    {
        pPlayer->ChangeState(new CJumpStartState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Z') && pPlayer->Dash_Check())
    {
        pPlayer->Set_LastDashTime();
        pPlayer->ChangeState(new CDashState());
        return;
    }

    return;
}

void CAttackState::Exit(CPlayer* pPlayer)
{
    m_bQueued = false;
}

EPlayerState CAttackState::GetStateID() const
{
    return EPlayerState::ATTACK;
}
