#include "pch.h"
#include "CBossDuoShootingLightning.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CLightningProjectile.h"
#include "CBossIdleState.h"
#include "CBossController.h"

constexpr float kStartWaitDuration = 1.f;

void CBossDuoShootingLightning::Enter(CBoss* pBoss)
{
    m_fElapsed = 0.f;
    m_iPhase = 0;

    //float fDirection = (CObjMgr::Get_Instance()->Get_Player()->Get_Info()->fX > pBoss->Get_Info()->fX) ? 1.f : -1.f;
    int id = pBoss->Get_ID();
    if (id == 0)
    {
        pBoss->Set_Pos(50.f, 400.f);
        m_Offsets = {
            Vec2(0, -40),   // 머리 위
            Vec2(30, -10),  // 어깨 근처
            Vec2(20, 0)     // 몸 앞
        };
        pBoss->Set_Frame(0, 3, 2, 450);
    }
    else
    {
        pBoss->Set_Pos(WINCX - 50.f, 400.f);
        m_Offsets = {
            Vec2(0, -40),   // 머리 위
            Vec2(-30, -10),  // 어깨 근처
            Vec2(-20, 0)     // 몸 앞
        };
        pBoss->Set_Frame(0, 3, 3, 450);
    }
}

void CBossDuoShootingLightning::Update(CBoss* pBoss)
{
    m_fElapsed += DELTA_TIME;

    if (m_fElapsed >= kStartWaitDuration)
    {
        if (m_iPhase < 3 && m_fElapsed >= m_iPhase * 0.3f)
        {
            Vec2 bossPos(pBoss->Get_Info()->fX, pBoss->Get_Info()->fY);
            Vec2 firePos = bossPos + m_Offsets[m_iPhase];

            CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
            Vec2 playerPos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
            Vec2 dir = playerPos - firePos;
            dir.Normalize();
            CObj* pProj = new CLightningProjectile(firePos, dir);
            pProj->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_PROJECTILE, pProj);

            ++m_iPhase;
        }

        if (m_fElapsed > 3.0f)
        {
            //pBoss->ChangeState(new CBossIdleState());
            if (pBoss->Get_ID() == g_iNextWaitBossID)
                pBoss->ChangeState(new CBossWaitState());
            else
                pBoss->ChangeState(new CBossIdleState());
        }
    }
}


void CBossDuoShootingLightning::Exit(CBoss* pBoss)
{
    // TODO: 종료 처리
}

EBossStateType CBossDuoShootingLightning::GetType()
{
    return EBossStateType::DuoLightning;
}
