#include "pch.h"
#include "CBossDuoDive.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CBossIdleState.h"
#include "CPlayer.h"
#include "CBossController.h"

void CBossDuoDive::Enter(CBoss* pBoss)
{
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

    // 공중 위치로 세팅
    //float spawnX = pBoss->Get_Info()->fX;
    float spawnX = CObjMgr::Get_Instance()->Get_Player()->Get_Info()->fX;
    pBoss->Set_Pos(spawnX, -200.f);
    pBoss->Set_Frame(0, 10, 8, 50);
}

void CBossDuoDive::Update(CBoss* pBoss)
{
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
