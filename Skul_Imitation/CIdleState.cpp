#include "pch.h"
#include "CIdleState.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CWalkState.h"
#include "CAttackState.h"
#include "CDashState.h"
#include "CJumpStartState.h"

void CIdleState::Enter(CPlayer* pPlayer)
{
	//pPlayer->Set_FrameKey(L"Player_RIGHT");
    pPlayer->Set_Frame(0, 3, 0, 200);
}

void CIdleState::Update(CPlayer* pPlayer)
{
    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
    {
        pPlayer->ChangeState(new CWalkState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('X'))
    {
        pPlayer->ChangeState(new CAttackState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Z') && pPlayer->Dash_Check())
    {
        pPlayer->Set_LastDashTime();
        pPlayer->ChangeState(new CDashState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('C') && !pPlayer->Get_IsJump())
    {
        pPlayer->ChangeState(new CJumpStartState());
        return;
    }

    pPlayer->Move_Frame();
}

void CIdleState::Exit(CPlayer* pPlayer)
{
}

EPlayerState CIdleState::GetStateID() const
{
	return EPlayerState::IDLE;
}
