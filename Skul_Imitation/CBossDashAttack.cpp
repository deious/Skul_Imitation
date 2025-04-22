#include "pch.h"
#include "CBossDashAttack.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CBossIdleState.h"
#include "CPlayer.h"
#include "CEffectMgr.h"
#include "CTimeMgr.h"

void CBossDashAttack::Enter(CBoss* pBoss)
{
    pBoss->Set_AnimStatus(false);
    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();

    if (!pPlayer) return;

    CHitBox* pHitBox = pPlayer->Get_HitBox();
    if (!pHitBox) return;

    pHitBox->Reset_HitCount();
    pHitBox->Set_MaxHits(1);

    m_fElapsed = 0.f;
    m_bAttacked = false;

    // 방향 계산
    //CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    //if (!pPlayer) return;

    fDirection = (pPlayer->Get_Info()->fX > pBoss->Get_Info()->fX) ? 1.f : -1.f;
    pBoss->Set_Speed(fDirection * m_fDashSpeed);
    if (fDirection > 0)
    {
        if (pBoss->IsAwakened())
        {
            pBoss->Set_FrameKey(L"Boss_Dash_Right");
            pBoss->Set_Frame(0, 4, 0, 100);
        }
        else
        {
            pBoss->Set_Frame(0, 4, 4, 100);
            m_sEffectKey = L"BossDash_Right";
        }
    }
    else
    {
        if (pBoss->IsAwakened())
        {
            pBoss->Set_FrameKey(L"Boss_Dash_Left");
            pBoss->Set_Frame(0, 4, 0, 100);
        }
        else
        {
            pBoss->Set_Frame(0, 4, 5, 100);
            m_sEffectKey = L"BossDash_Left";
        }
    }

    EffectInfo effect;
    effect.eType = EFFECT_TYPE::SKILLA;
    effect.sFramekey = m_sEffectKey.c_str();
    effect.vOffset;
    effect.vSize = Vec2(173.f, 77.f); // 이펙트 크기
    effect.iStartFrame = 0;
    effect.iEndFrame = 5;
    effect.iFrameSpeed = 50;
    effect.fScale = 1.f;
    effect.fRotation = 0.f;

    CEffectMgr::Get_Instance()->Add_Effect(effect, { pBoss->Get_Info()->fX, pBoss->Get_Info()->fY });
    /*WCHAR szBuffer[128];
    swprintf_s(szBuffer, L"[Enter] 보스 방향: %.1f, 속도: %.1f\n", fDirection, pBoss->Get_Speed());
    OutputDebugString(szBuffer);*/
}

void CBossDashAttack::Update(CBoss* pBoss)
{
    /*if (!pBoss || pBoss->IsDead())
        return;*/

    m_fElapsed += DELTA_TIME;

    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    if (!pPlayer) return;

    float distance = abs(pBoss->Get_Info()->fX - pPlayer->Get_Info()->fX);

    /*wchar_t szBuffer[128];
    swprintf_s(szBuffer, L"[Update] 시간: %.2f, 보스X: %.2f, 거리: %.2f, 속도: %.2f, m_bAttacked: %d\n",
        m_fElapsed, pBoss->Get_Info()->fX, distance, pBoss->Get_Speed(), m_bAttacked);
    OutputDebugString(szBuffer);*/

    if (!m_bAttacked && (distance < 30.f || m_fElapsed > 0.55f))
    {
        float x = pBoss->Get_Info()->fX + ((fDirection > 0) ? 40.f : -40.f);
        float y = pBoss->Get_Info()->fY;

        CAttackCollider* pCol = new CAttackCollider(
            pBoss, x, y,
            60.f, 30.f, 0.f, 0.2f,
            CAttackCollider::ColliderType::Static,
            ETeam::Enemy,
            ESkillType::Attack,
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


EBossStateType CBossDashAttack::GetType()
{
    return EBossStateType::DashAttack;
}
