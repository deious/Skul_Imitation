#include "pch.h"
#include "CBossDuoDive.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CBossIdleState.h"
#include "CPlayer.h"
#include "CBossController.h"
#include "CEffectMgr.h"
#include "CTimeMgr.h"

void CBossDuoDive::Enter(CBoss* pBoss)
{
    pBoss->Set_AnimStatus(false);
    list<CObj*>& bossList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER);
    for (CObj* pObj : bossList)
    {
        if (!pObj || pObj->Get_Dead()) continue;

        CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
        if (!pPlayer) continue;

        CHitBox* pHitBox = pPlayer->Get_HitBox();
        if (!pHitBox) continue;

        pHitBox->Reset_HitCount();
        pHitBox->Set_MaxHits(1);
    }

    m_bDived = false;
    m_fWaitTime = 0.f;
    m_sEffectKey = L"BossDive";
    // 공중 위치로 세팅
    //float spawnX = pBoss->Get_Info()->fX;
    float spawnX = CObjMgr::Get_Instance()->Get_Player()->Get_Info()->fX;
    pBoss->Set_Pos(spawnX, -200.f);
    if (pBoss->IsAwakened())
    {
        pBoss->Set_FrameKey(L"Boss_Dive");
        pBoss->Set_Frame(0, 10, 0, 150);
        m_tEffectInfo.eType = EFFECT_TYPE::SKILLA;
        m_tEffectInfo.sFramekey = L"Dark_Dead_Outro_sheet";
        m_tEffectInfo.vOffset = { 0.f, -50.f };
        m_tEffectInfo.vSize = Vec2(89.f, 354.f); // 이펙트 크기
        m_tEffectInfo.iStartFrame = 0;
        m_tEffectInfo.iEndFrame = 33;
        m_tEffectInfo.iFrameSpeed = 10;
        m_tEffectInfo.fScale = 1.f;
        m_tEffectInfo.fRotation = 0.f;
    }
    else
    {
        pBoss->Set_Frame(0, 10, 8, 150);
        m_tEffectInfo.eType = EFFECT_TYPE::SKILLA;
        m_tEffectInfo.sFramekey = m_sEffectKey.c_str();
        m_tEffectInfo.vOffset = { 0.f, -50.f };
        m_tEffectInfo.vSize = Vec2(51.2f, 256.f); // 이펙트 크기
        m_tEffectInfo.iStartFrame = 0;
        m_tEffectInfo.iEndFrame = 9;
        m_tEffectInfo.iFrameSpeed = 30;
        m_tEffectInfo.fScale = 1.f;
        m_tEffectInfo.fRotation = 0.f;
    }

    //CEffectMgr::Get_Instance()->Add_Effect(effect, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY }, pBoss);
}

void CBossDuoDive::Update(CBoss* pBoss)
{
    /*if (!pBoss || pBoss->IsDead())
        return;*/

    m_fWaitTime += DELTA_TIME;

    if (!m_bDived && m_fWaitTime >= 0.5f)
    {
        float curY = pBoss->Get_Info()->fY;
        if (curY < 450.f)
        {
            //m_fTargetY
            pBoss->Set_Pos(pBoss->Get_Info()->fX, curY + m_fDiveSpeed);
        }
        else
        {
            m_bDived = true;
            CEffectMgr::Get_Instance()->Add_Effect(m_tEffectInfo, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY }, pBoss);
            CAttackCollider* pCol = new CAttackCollider(
                pBoss, pBoss->Get_Info()->fX, 450.f,
                100.f, 50.f, 0.f, 0.3f,
                CAttackCollider::ColliderType::Follow,
                ETeam::Enemy,
                ESkillType::Attack,
                30
            );
            pCol->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
        }
    }

    if (m_bDived && m_fWaitTime > 1.5f)
    {
        //pBoss->ChangeState(new CBossIdleState());
        if (pBoss->Get_ID() == g_iNextWaitBossID)
            pBoss->ChangeState(new CBossWaitState());
        else
            pBoss->ChangeState(new CBossIdleState());
    }
}

void CBossDuoDive::Exit(CBoss* pBoss)
{
    pBoss->Set_Speed(0.f);
}

EBossStateType CBossDuoDive::GetType()
{
    return EBossStateType::DuoDive;
}
