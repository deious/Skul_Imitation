#include "pch.h"
#include "CBossDuoShootingLightning.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CLightningProjectile.h"
#include "CBossIdleState.h"
#include "CBossController.h"
#include "CTimeMgr.h"

constexpr float kStartWaitDuration = 1.f;
float kPhaseInterval = 0.7f;
float fAwakenInterval = 0.3f;

void CBossDuoShootingLightning::Enter(CBoss* pBoss)
{
    pBoss->Set_AnimStatus(false);
    m_fElapsed = 0.f;
    m_iPhase = 0;

    //float fDirection = (CObjMgr::Get_Instance()->Get_Player()->Get_Info()->fX > pBoss->Get_Info()->fX) ? 1.f : -1.f;
    int id = pBoss->Get_ID();
    if (pBoss->IsAwakened())
    {
        int randNum = CRandomMgr::Get_Instance()->GetRandom(0, 1);
        if (randNum == 0)
        {
            pBoss->Set_FrameKey(L"BossHoming_Right");
            pBoss->Set_Frame(0, 10, 0, 150);
            pBoss->Set_Pos(50.f, 400.f);
            m_Offsets = {
            Vec2(0, -40),   // ¸Ó¸® À§
            Vec2(30, -10),  // ¾î±ú ±ÙÃ³
            Vec2(20, 0),     // ¸ö ¾Õ
            Vec2(50, -40),
            Vec2(70, -60),
            Vec2(10, -80)
            };
        }
        else
        {
            pBoss->Set_FrameKey(L"BossHoming_Left");
            pBoss->Set_Frame(0, 10, 0, 150);
            pBoss->Set_Pos(WINCX - 50.f, 400.f);
            m_Offsets = {
            Vec2(0, -40),   // ¸Ó¸® À§
            Vec2(-30, -10),  // ¾î±ú ±ÙÃ³
            Vec2(-20, 0),     // ¸ö ¾Õ
            Vec2(-50, -40),
            Vec2(-70, -60),
            Vec2(-10, -80)
            };
        }
    }
    else if (id == 0)
    {
        pBoss->Set_Pos(50.f, 400.f);
        m_Offsets = {
            Vec2(0, -40),   // ¸Ó¸® À§
            Vec2(30, -10),  // ¾î±ú ±ÙÃ³
            Vec2(20, 0)     // ¸ö ¾Õ
        };
        pBoss->Set_Frame(0, 3, 2, 450);
    }
    else
    {
        pBoss->Set_Pos(WINCX - 50.f, 400.f);
        m_Offsets = {
            Vec2(0, -40),   // ¸Ó¸® À§
            Vec2(-30, -10),  // ¾î±ú ±ÙÃ³
            Vec2(-20, 0)     // ¸ö ¾Õ
        };
        pBoss->Set_Frame(0, 3, 3, 450);
    }
}

void CBossDuoShootingLightning::Update(CBoss* pBoss)
{
    /*if (!pBoss || pBoss->IsDead())
        return;*/
    m_fElapsed += DELTA_TIME;

    if (m_fElapsed >= kStartWaitDuration)
    {
        if (pBoss->IsAwakened())
        {
            if (m_iPhase < 6 && m_fElapsed >= kStartWaitDuration + m_iPhase * fAwakenInterval)
            {
                Vec2 bossPos(pBoss->Get_Info()->fX, pBoss->Get_Info()->fY);
                Vec2 firePos = bossPos + m_Offsets[m_iPhase];

                CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
                Vec2 playerPos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
                Vec2 dir = playerPos - firePos;
                dir.Normalize();

                CObj* pProj = new CLightningProjectile(firePos, dir, pBoss->Get_ID());
                pProj->Initialize();
                CObjMgr::Get_Instance()->Add_Object(OBJ_PROJECTILE, pProj);

                ++m_iPhase;
            }
        }
        else
        {
            if (m_iPhase < 3 && m_fElapsed >= kStartWaitDuration + m_iPhase * kPhaseInterval)
            {
                Vec2 bossPos(pBoss->Get_Info()->fX, pBoss->Get_Info()->fY);
                Vec2 firePos = bossPos + m_Offsets[m_iPhase];

                CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
                Vec2 playerPos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
                Vec2 dir = playerPos - firePos;
                dir.Normalize();

                CObj* pProj = new CLightningProjectile(firePos, dir, pBoss->Get_ID());
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
}


void CBossDuoShootingLightning::Exit(CBoss* pBoss)
{
    // TODO: Á¾·á Ã³¸®
}

EBossStateType CBossDuoShootingLightning::GetType()
{
    return EBossStateType::DuoLightning;
}
