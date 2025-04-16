#include "pch.h"
#include "CBossIdleState.h"

void CBossIdleState::Enter(CBoss* pBoss)
{
    int id = pBoss->Get_ID();
    if (id == 0)
    {
        pBoss->Set_Frame(0, 7, 0, 200);
    }
    else
    {
        pBoss->Set_Frame(0, 7, 1, 200);
    }
}

void CBossIdleState::Update(CBoss* pBoss) {}

void CBossIdleState::Exit(CBoss* pBoss) {}

EBossStateType CBossIdleState::GetType()
{
	return EBossStateType::Idle;
}
