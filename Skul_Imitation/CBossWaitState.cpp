#include "pch.h"
#include "CBossWaitState.h"
#include "CBossIdleState.h"

void CBossWaitState::Enter(CBoss* pBoss)
{
	pBoss->Set_AnimStatus(false);
	pBoss->Set_Speed(0.f);
	pBoss->Set_Frame(0, 4, 13, 100);
	pBoss->Set_Pos(250.f, 260.f);
	pBoss->Set_Gravity();
	pBoss->Set_Invincibility(true);
	//pBoss->Update_Rect();
	//pBoss->Get_HitBox()->Set_Pos(100.f, 200.f);
	//pBoss->Get_HitBox()->Update_Rect();
}

void CBossWaitState::Update(CBoss* pBoss)
{
	/*if (!pBoss || pBoss->IsDead())
		return;*/
	/*if (g_bIsTeamPatternTime)
	{
		pBoss->Set_Gravity();
		pBoss->ChangeState(new CBossIdleState());
	}*/
}

void CBossWaitState::Exit(CBoss* pBoss)
{
	pBoss->Set_Invincibility(false);
	pBoss->Set_Gravity();
}

EBossStateType CBossWaitState::GetType()
{
	return EBossStateType::Wait;
}
