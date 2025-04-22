#include "pch.h"
#include "CBossAttackState.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CBossIdleState.h"
#include "CTimeMgr.h"

void CBossAttackState::Enter(CBoss* pBoss)
{
    m_fElapsed = 0.f;
    m_bAttacked = false;
    pBoss->Set_Frame(0, 6, 4, 200);
    OutputDebugString(L"[보스 공격 시작]\n");
}

void CBossAttackState::Update(CBoss* pBoss)
{
    m_fElapsed += DELTA_TIME;

    if (!m_bAttacked && m_fElapsed >= 0.2f)
    {
        float x = pBoss->Get_Info()->fX + 50.f;
        float y = pBoss->Get_Info()->fY;
        CAttackCollider* pCol = new CAttackCollider(
            pBoss, x, y,
            80.f, 60.f, 0.f, 0.3f,
            CAttackCollider::ColliderType::Static,
            ETeam::Enemy,
            ESkillType::Attack,
            30
        );
        pCol->Initialize();
        CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
        m_bAttacked = true;
    }

    if (m_fElapsed >= 1.0f)
    {
        pBoss->ChangeState(new CBossIdleState());
    }
}


void CBossAttackState::Exit(CBoss* pBoss)
{
    OutputDebugString(L"[보스 공격 종료]\n");
}
