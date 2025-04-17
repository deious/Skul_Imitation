#include "pch.h"
#include "CJumpStartState.h"
#include "CPlayer.h"
#include "CRisingState.h"
#include "CKeyMgr.h"
#include "CDashState.h"
#include "CAttackState.h"
#include "CSoundMgr.h"

void CJumpStartState::Enter(CPlayer* pPlayer)
{
	pPlayer->Set_Frame(0, 1, 3, 200);
    pPlayer->Set_Gravity(pPlayer->Get_JumpPower());
    pPlayer->Set_Jump(true);
    pPlayer->Add_JumpCnt();
    pPlayer->Get_Skul()->PlayJumpEffect();
    CSoundMgr::Get_Instance()->Play(L"Default_Jump.wav");
}

void CJumpStartState::Update(CPlayer* pPlayer)
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
        //pPlayer->Add_JumpCnt();
        pPlayer->ChangeState(new CJumpStartState());
        return;
    }

    if (pPlayer->Move_Frame())
    {
        pPlayer->ChangeState(new CRisingState());
    }
}

void CJumpStartState::Exit(CPlayer* pPlayer)
{
}

EPlayerState CJumpStartState::GetStateID() const { return EPlayerState::JUMPSTART; }

