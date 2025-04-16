#include "pch.h"
#include "CFallState.h"
#include "CPlayer.h"
#include "CIdleState.h"
#include "CDashState.h"
#include "CKeyMgr.h"
#include "CAttackState.h"
#include "CJumpStartState.h"

void CFallState::Enter(CPlayer* pPlayer)
{
    pPlayer->Set_Frame(0, 2, 5, 200);
}

void CFallState::Update(CPlayer* pPlayer)
{
    if (CKeyMgr::Get_Instance()->Key_Down('Z'))
    {
        pPlayer->ChangeState(new CDashState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('X'))
    {
        pPlayer->ChangeState(new CAttackState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT)) 
    {
        pPlayer->Set_PosX(-pPlayer->Get_Speed());
        pPlayer->Set_Direction(DIRECTION::DIR_LEFT);
    }
    else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT)) 
    {
        pPlayer->Set_PosX(pPlayer->Get_Speed());
        pPlayer->Set_Direction(DIRECTION::DIR_RIGHT);
    }

    if (CKeyMgr::Get_Instance()->Key_Down('C') && pPlayer->Get_JumpCnt() < pPlayer->Get_JumpMaxCnt())
    {
        pPlayer->Add_JumpCnt();
        pPlayer->ChangeState(new CJumpStartState());
        return;
    }

    float gravity = pPlayer->Get_Gravity() + pPlayer->Get_GravityAccel();
    gravity = min(gravity, pPlayer->Get_GravityMax());

    pPlayer->Set_Gravity(gravity);
    pPlayer->Set_PosY(gravity);
    pPlayer->Move_Frame();

    if (!pPlayer->Get_IsJump()) // ¶¥¿¡ ÂøÁö ½Ã
    {
        pPlayer->ChangeState(new CIdleState());
    }
}

EPlayerState CFallState::GetStateID() const { return EPlayerState::FALL; }

void CFallState::Exit(CPlayer* pPlayer) {}
