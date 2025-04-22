#include "pch.h"
#include "CBossDieState.h"
#include "CEffectMgr.h"
#include "CObjMgr.h"
#include "CGate.h"


void CBossDieState::Enter(CBoss* pBoss)
{
	if (pBoss->IsAwakened())
	{
		pBoss->Set_FrameKey(L"Dark_Dead_Body_sheet");
		pBoss->Set_Frame(0, 47, 0, 100);

        EffectInfo eInfo;
        eInfo.eType = EFFECT_TYPE::SKILLA;
        eInfo.sFramekey = L"Dark_Dead_Electric2_sheet";
        eInfo.vOffset = {0.f, -70.f};
        eInfo.vSize = Vec2(200.f, 200.f); // 이펙트 크기
        eInfo.iStartFrame = 0;
        eInfo.iEndFrame = 10;
        eInfo.iFrameSpeed = 200;
        eInfo.fScale = 1.f;
        eInfo.fRotation = 0.f;

        EffectInfo eInfo_1;
        eInfo_1.eType = EFFECT_TYPE::SKILLA;
        eInfo_1.sFramekey = L"Dark_Dead_Intro_sheet";
        eInfo_1.vOffset = { 0.f, -100.f };
        eInfo_1.vSize = Vec2(210.f, 400.f); // 이펙트 크기
        eInfo_1.iStartFrame = 0;
        eInfo_1.iEndFrame = 5;
        eInfo_1.iFrameSpeed = 250;
        eInfo_1.fScale = 1.f;
        eInfo_1.fRotation = 0.f;

        EffectInfo eInfo_2;
        eInfo_2.eType = EFFECT_TYPE::SKILLA;
        eInfo_2.sFramekey = L"Dark_Dead_Loop_sheet";
        eInfo_2.vOffset = { 0.f, -100.f };
        eInfo_2.vSize = Vec2(210.f, 400.f); // 이펙트 크기
        eInfo_2.iStartFrame = 0;
        eInfo_2.iEndFrame = 8;
        eInfo_2.iFrameSpeed = 250;
        eInfo_2.fScale = 1.f;
        eInfo_2.fRotation = 0.f;

        EffectInfo eInfo_3;
        eInfo_3.eType = EFFECT_TYPE::SKILLA;
        eInfo_3.sFramekey = L"Dark_Dead_Outro_sheet";
        eInfo_3.vOffset;
        eInfo_3.vSize = Vec2(89.f, 354.f); // 이펙트 크기
        eInfo_3.iStartFrame = 0;
        eInfo_3.iEndFrame = 33;
        eInfo_3.iFrameSpeed = 100;
        eInfo_3.fScale = 1.f;
        eInfo_3.fRotation = 0.f;

        CEffectMgr::Get_Instance()->Add_Effect(eInfo, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });
        CEffectMgr::Get_Instance()->Add_Effect(eInfo_1, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });
        CEffectMgr::Get_Instance()->Add_Effect(eInfo_2, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });
        CEffectMgr::Get_Instance()->Add_Effect(eInfo_3, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });
	}
    else
    {
        pBoss->Set_Frame(0, 4, 17, 300);
    }
}

void CBossDieState::Update(CBoss* pBoss)
{
}

void CBossDieState::Exit(CBoss* pBoss)
{
    pBoss->Set_Dead();

    if (!HasEndingGate() && AllBossDead())
    {
        INFO gateInfo;
        gateInfo.fX = 400.f;  // 화면 중앙
        gateInfo.fY = 350.f;
        gateInfo.fCX = 200.f;
        gateInfo.fCY = 200.f;


        CGate* pEndingGate = new CGate(L"StageDoor", gateInfo, 5);
        dynamic_cast<CGate*>(pEndingGate)->Set_Frame(0, 7, 50.f);
        pEndingGate->Set_Condition([]() { return true; });

        CObjMgr::Get_Instance()->Add_Object(OBJ_TRIGGER, pEndingGate);
    }
}

bool CBossDieState::HasEndingGate()
{
    for (auto pObj : CObjMgr::Get_Instance()->Get_ObjList(OBJ_TRIGGER))
    {
        if (pObj->Get_FrameKey() == L"StageDoor")
            return true;
    }
    return false;
}

bool CBossDieState::AllBossDead()
{
    auto& bossList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS);
    for (CObj* pBoss : bossList)
    {
        if (!pBoss->Get_Dead()) // 하나라도 살아 있으면 false
            return false;
    }
    return true;
}
