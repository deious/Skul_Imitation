#include "pch.h"
#include "CRisingState.h"
#include "CPlayer.h"
#include "CFallState.h"
#include "CDashState.h"
#include "CKeyMgr.h"

void CRisingState::Enter(CPlayer* pPlayer)
{
    pPlayer->Set_Frame(0, 1, 4, 200);
}

void CRisingState::Update(CPlayer* pPlayer)
{
    if (CKeyMgr::Get_Instance()->Key_Down('Z')) // 대시
    {
        pPlayer->ChangeState(new CDashState());
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

    float gravity = pPlayer->Get_Gravity() + pPlayer->Get_GravityAccel();
    pPlayer->Set_Gravity(gravity);
    pPlayer->Set_PosY(-gravity);
    pPlayer->Move_Frame();

    if (gravity > 0.f) // 정점 도달
    {
        pPlayer->ChangeState(new CFallState());
    }
}

EPlayerState CRisingState::GetStateID() const { return EPlayerState::RISING; }

void CRisingState::Exit(CPlayer* pPlayer) {}
