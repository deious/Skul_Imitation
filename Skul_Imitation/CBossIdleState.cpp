#include "pch.h"
#include "CBossIdleState.h"

void CBossIdleState::Enter(CBoss* pBoss)
{
	pBoss->Set_Frame(0, 7, 0, 200);
}

void CBossIdleState::Update(CBoss* pBoss) {}

void CBossIdleState::Exit(CBoss* pBoss) {}
