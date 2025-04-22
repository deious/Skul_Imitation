#include "pch.h"
#include "CBossIdleState.h"

void CBossIdleState::Enter(CBoss* pBoss)
{
    OutputDebugString(L"[IdleState] Enter()\n");
    pBoss->Set_AnimStatus(false);
    int id = pBoss->Get_ID();
    if (dynamic_cast<CBoss*>(pBoss)->IsAwakened())
    {
        pBoss->Set_FrameKey(L"Boss_Idle");
        pBoss->Set_Frame(0, 8, 0, 100);
    }
    else if (id == 0)
    {
        pBoss->Set_Frame(0, 7, 0, 200);
    }
    else
    {
        pBoss->Set_Frame(0, 7, 1, 200);
    }

}

void CBossIdleState::Update(CBoss* pBoss) {
    /*if (!pBoss || pBoss->IsDead())
        return;*/
}

void CBossIdleState::Exit(CBoss* pBoss) {}

EBossStateType CBossIdleState::GetType()
{
	return EBossStateType::Idle;
}
