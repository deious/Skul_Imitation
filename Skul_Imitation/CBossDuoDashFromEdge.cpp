#include "pch.h"
#include "CBossDuoDashFromEdge.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CBossIdleState.h"
#include "CBossController.h"

constexpr float kStartWaitDuration = 0.5f; // ���� �� ���ð�

void CBossDuoDashFromEdge::Enter(CBoss* pBoss)
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

    m_fWaitTime = 0.f;
    m_fDashTime = 0.f;
    m_bDashed = false;

    float groundY = 400.f; // ���� ��
    float screenWidth = WINCX;

    // ID�� ����/������ ����
    if (pBoss->Get_ID() == 0)
        pBoss->Set_Pos(50.f, groundY);
    else
        pBoss->Set_Pos(screenWidth - 50.f, groundY);

    // ��� �ִϸ��̼� ���� �� ����
    //pBoss->Set_Frame(/*����������*/, /*����������*/, /*���Ÿ��*/, /*�ӵ�*/);
    pBoss->Set_Frame(0, 3, 2, 100);
}

void CBossDuoDashFromEdge::Update(CBoss* pBoss)
{
    m_fWaitTime += DELTA_TIME;

    if (!m_bDashed && m_fWaitTime >= kStartWaitDuration)
    {
        CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
        if (!pPlayer) return;

        float direction = (pPlayer->Get_Info()->fX > pBoss->Get_Info()->fX) ? 1.f : -1.f;
        pBoss->Set_Speed(direction * m_fDashSpeed);

        m_bDashed = true;
        pBoss->Set_Frame(0, 5, 9, 100);

        float x = pBoss->Get_Info()->fX + 50.f;
        float y = pBoss->Get_Info()->fY;
        CAttackCollider* pCol = new CAttackCollider(
            pBoss, x, y,
            80.f, 60.f, 0.f, 1.f,
            CAttackCollider::ColliderType::Follow,
            ETeam::Enemy,
            30
        );
        pCol->Initialize();
        CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
    }

    if (m_bDashed)
    {
        m_fDashTime += DELTA_TIME;

        if (m_fDashTime >= 1.0f) // ���� ��¥ "���� �ð�" ����
        {
            pBoss->Set_Speed(0.f);
            //pBoss->ChangeState(new CBossIdleState());
            if (pBoss->Get_ID() == g_iNextWaitBossID)
                pBoss->ChangeState(new CBossWaitState());
            else
                pBoss->ChangeState(new CBossIdleState());
        }
    }
}

void CBossDuoDashFromEdge::Exit(CBoss* pBoss)
{
    pBoss->Set_Speed(0.f); // ����
}

EBossStateType CBossDuoDashFromEdge::GetType()
{
    return EBossStateType::DuoDash;
}
