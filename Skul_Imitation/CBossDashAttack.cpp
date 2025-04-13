#include "pch.h"
#include "CBossDashAttack.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CBossIdleState.h"
#include "CPlayer.h"

void CBossDashAttack::Enter(CBoss* pBoss)
{
    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

    if (!pPlayer) return;

    CHitBox* pHitBox = pPlayer->Get_HitBox();
    if (!pHitBox) return;

    pHitBox->Reset_HitCount();
    pHitBox->Set_MaxHits(1);

    m_fElapsed = 0.f;
    m_bAttacked = false;

    // ���� ���
    //CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    //if (!pPlayer) return;

    fDirection = (pPlayer->Get_Info()->fX > pBoss->Get_Info()->fX) ? 1.f : -1.f;
    pBoss->Set_Speed(fDirection * m_fDashSpeed);

    /*WCHAR szBuffer[128];
    swprintf_s(szBuffer, L"[Enter] ���� ����: %.1f, �ӵ�: %.1f\n", fDirection, pBoss->Get_Speed());
    OutputDebugString(szBuffer);*/
}

void CBossDashAttack::Update(CBoss* pBoss)
{
    m_fElapsed += DELTA_TIME;

    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    if (!pPlayer) return;

    float distance = abs(pBoss->Get_Info()->fX - pPlayer->Get_Info()->fX);

    wchar_t szBuffer[128];
    swprintf_s(szBuffer, L"[Update] �ð�: %.2f, ����X: %.2f, �Ÿ�: %.2f, �ӵ�: %.2f, m_bAttacked: %d\n",
        m_fElapsed, pBoss->Get_Info()->fX, distance, pBoss->Get_Speed(), m_bAttacked);
    OutputDebugString(szBuffer);

    if (!m_bAttacked && (distance < 30.f || m_fElapsed > 0.55f))
    {
        float x = pBoss->Get_Info()->fX + ((fDirection > 0) ? 40.f : -40.f);
        float y = pBoss->Get_Info()->fY;

        CAttackCollider* pCol = new CAttackCollider(
            pBoss, x, y,
            60.f, 30.f, 0.f, 0.2f,
            CAttackCollider::ColliderType::Static,
            ETeam::Enemy,
            25
        );
        pCol->Initialize();
        CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
        m_bAttacked = true;
    }

    if (m_fElapsed >= m_fDashDuration)
    {
        pBoss->Set_Speed(0.f);
        pBoss->ChangeState(new CBossIdleState());
    }
}

void CBossDashAttack::Exit(CBoss* pBoss)
{
    pBoss->Set_Speed(0.f);
}
