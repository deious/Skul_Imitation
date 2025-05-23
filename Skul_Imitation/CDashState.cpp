#include "pch.h"
#include "CDashState.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CAttackState.h"
#include "CIdleState.h"
#include "CJumpStartState.h"
#include "CSoundMgr.h"

void CDashState::Enter(CPlayer* pPlayer)
{
    if (pPlayer->Get_UseGravity())
    {
        pPlayer->Set_UseGravity();
    }
    m_dwStartTime = GetTickCount64();
    pPlayer->Set_Frame(0, 0, 2, 100);
    pPlayer->Get_Skul()->PlayDashEffect();
    CSoundMgr::Get_Instance()->Play(L"Default_Dash.wav");
}

void CDashState::Update(CPlayer* pPlayer)
{
    if (CKeyMgr::Get_Instance()->Key_Down('X'))
    {
        pPlayer->ChangeState(new CAttackState());
        return;
    }

    if (pPlayer->Get_Direction() == DIRECTION::DIR_LEFT)
    {
        pPlayer->Set_PosX(-pPlayer->Get_Speed() * 3.f);
    }
    else
    {
        pPlayer->Set_PosX(pPlayer->Get_Speed() * 3.f);
    }

    if (CKeyMgr::Get_Instance()->Key_Down('C') && pPlayer->Get_JumpCnt() < pPlayer->Get_JumpMaxCnt())
    {
        //pPlayer->Add_JumpCnt();
        pPlayer->ChangeState(new CJumpStartState());
        return;
    }

    if (GetTickCount64() - m_dwStartTime > pPlayer->Get_DashDuration())
    {
        pPlayer->ChangeState(new CIdleState());
        return;
    }

    pPlayer->Move_Frame();
}

void CDashState::Exit(CPlayer* pPlayer)
{
    pPlayer->Set_UseGravity();
}

EPlayerState CDashState::GetStateID() const
{
    return EPlayerState();
}
