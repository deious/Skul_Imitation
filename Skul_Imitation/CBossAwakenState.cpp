#include "pch.h"
#include "CBossAwakenState.h"
#include "CBoss.h"
#include "CBossIdleState.h"
#include "CEffectMgr.h"

void CBossAwakenState::Enter(CBoss* pBoss)
{
    OutputDebugString(L"[AwakenState] Enter()\n");
    pBoss->Set_AnimFinish();
    pBoss->Set_FrameKey(L"Awaken_2");
    pBoss->Set_Frame(0, 34, 0, 70);
    EffectInfo effect;
    effect.eType = EFFECT_TYPE::SKILLA;
    effect.sFramekey = L"Awaken_Electric_sheet";
    effect.vOffset;
    effect.vSize = Vec2(202.f, 158.f); // 이펙트 크기
    effect.iStartFrame = 0;
    effect.iEndFrame = 56;
    effect.iFrameSpeed = 50;
    effect.fScale = 1.f;
    effect.fRotation = 0.f;

    CEffectMgr::Get_Instance()->Add_Effect(effect, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });

    effect.eType = EFFECT_TYPE::SKILLA;
    effect.sFramekey = L"Awaken_End_Flame-sheet";
    effect.vOffset = {0, -100.f};
    effect.vSize = Vec2(264.f, 200.f); // 이펙트 크기
    effect.iStartFrame = 0;
    effect.iEndFrame = 11;
    effect.iFrameSpeed = 20;
    effect.fScale = 1.f;
    effect.fRotation = 0.f;

    CEffectMgr::Get_Instance()->Add_Effect(effect, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });
    //pBoss->Set_AnimFinish();
}

void CBossAwakenState::Update(CBoss* pBoss)
{
    /*if (!pBoss || pBoss->IsDead())
        return;*/
    /*OutputDebugString(L"[AwakenState] Update 호출됨\n");
    if (pBoss->Move_Frame())
    {
        OutputDebugString(L"[AwakenState] 애니메이션 종료됨, 다음 상태 전환 준비됨\n");
        pBoss->ChangeState(new CBossIdleState());
    }*/
    //pBoss->ChangeState(new CBossIdleState());
}

void CBossAwakenState::Exit(CBoss* pBoss)
{
    //pBoss->ChangeState(new CBossIdleState());
}

EBossStateType CBossAwakenState::GetType()
{
    return EBossStateType::Awaken;
}