#include "pch.h"
#include "CWalkState.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CIdleState.h"
#include "CAttackState.h"
#include "CDashState.h"
#include "CJumpStartState.h"

void CWalkState::Enter(CPlayer* pPlayer)
{
    pPlayer->Set_Frame(0, 7, 1, 200);
    //pPlayer->Set_FrameKey(L"Player_RIGHT");
}

void CWalkState::Update(CPlayer* pPlayer)
{
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

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
    {
        pPlayer->Set_PosX(-pPlayer->Get_Speed());
        //pPlayer->Set_FrameKey(L"Player_LEFT");
        pPlayer->Set_Direction(EDirection::LEFT);
    }
    else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
    {
        pPlayer->Set_PosX(pPlayer->Get_Speed());
        //pPlayer->Set_FrameKey(L"Player_RIGHT");
        pPlayer->Set_Direction(EDirection::RIGHT);
    }
    else
    {
        pPlayer->ChangeState(new CIdleState());
        return;
    }

    pPlayer->Move_Frame();
}

void CWalkState::Exit(CPlayer* pPlayer)
{
}

EPlayerState CWalkState::GetStateID() const
{
    return EPlayerState::WALK;
}
