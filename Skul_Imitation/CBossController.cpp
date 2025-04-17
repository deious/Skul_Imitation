#include "pch.h"
#include "CBossController.h"

void CBossController::Initialize(CBoss* a, CBoss* b)
{
    m_pBossA = a;
    m_pBossB = b;
}

void CBossController::Update()
{
    if (!m_pBossA || !m_pBossB) return;

    if (m_pBossA->IsDead() || m_pBossB->IsDead())
    {
        CBoss* survivor = m_pBossA->IsDead() ? m_pBossB : m_pBossA;
        //survivor->RebuildPhase2Tree();
        return;
    }

    m_fTimer += DELTA_TIME;
    m_fSoloCooldown += DELTA_TIME;

    if (!m_bDidFirstTeamPattern)
    {
        m_pBossA->ChangeState(new CBossDuoDashFromEdge());
        m_pBossB->ChangeState(new CBossDuoDashFromEdge());

        m_bDidFirstTeamPattern = true;
        m_fTimer = 0.f;
        m_fSoloCooldown = 0.f;
        return;
    }

    if (m_fTimer >= 20.f)
    {
        m_fTimer = 0.f;
        m_fSoloCooldown = 0.f;

        //int randPattern = rand() % 3;
        int randPattern = CRandomMgr::Get_Instance()->GetRandom(0, 2);
        g_iNextWaitBossID = (rand() % 2 == 0 ? m_pBossA->Get_ID() : m_pBossB->Get_ID());

        if (randPattern == 1)
        {
            m_pBossA->ChangeState(CreateTeamPattern(randPattern));

            // 2. 두 번째 보스는 대기 상태 플래그 설정
            m_bScheduledSecondBoss = true;
            m_fSecondBossTimer = 0.f;
            m_fSecondBossDelay = 1.0f + CRandomMgr::Get_Instance()->GetRandom(0, 2) * 0.5f;

            m_fTimer = 0.f;
            m_fSoloCooldown = 0.f;
        }
        else
        {
            m_pBossA->ChangeState(CreateTeamPattern(randPattern));
            m_pBossB->ChangeState(CreateTeamPattern(randPattern));
        }

        g_bTeamPatternTime = true;
        //g_eNextTeamPattern = dynamic_cast<EBossStateType>(rand() % 3);

        // 누가 대기할지 랜덤
        /*int waitPick = rand() % 2;
        if (waitPick == 0)
        m_pBossA->ChangeState(new CBossWaitState());
        else
        m_pBossB->ChangeState(new CBossWaitState());*/
    }

    if (m_bScheduledSecondBoss)
    {
        m_fSecondBossTimer += DELTA_TIME;

        if (m_fSecondBossTimer >= m_fSecondBossDelay)
        {
            m_pBossB->ChangeState(CreateTeamPattern(1)); // 1번 패턴 실행
            m_bScheduledSecondBoss = false;
            m_fSecondBossTimer = 0.f;
        }
    }

    if (m_fSoloCooldown >= 5.0f && m_fTimer < 20.f)
    {
        /*if (m_pBossA->Get_CurStateType() == EBossStateType::Wait ||
        m_pBossB->Get_CurStateType() == EBossStateType::Wait)
        return;*/

        /*int pick = rand() % 2;
        CBoss* candidate1 = (pick == 0) ? m_pBossA : m_pBossB;
        CBoss* candidate2 = (pick == 0) ? m_pBossB : m_pBossA;*/
        int pick = CRandomMgr::Get_Instance()->GetRandom(0, 1);

        CBoss* candidate1 = (pick == 0) ? m_pBossA : m_pBossB;
        CBoss* candidate2 = (pick == 0) ? m_pBossB : m_pBossA;

        CBoss* soloBoss = nullptr;
        if (candidate1->Get_CurStateType() != EBossStateType::Wait)
            soloBoss = candidate1;
        else if (candidate2->Get_CurStateType() != EBossStateType::Wait)
            soloBoss = candidate2;

        if (soloBoss == m_pBossA)
            m_pBossB->ChangeState(new CBossWaitState());
        else
            m_pBossA->ChangeState(new CBossWaitState());


        /*CBoss* soloBoss = nullptr;
        CBoss* waitBoss = nullptr;
        int iRandPick = rand() % 2;
        waitBoss = (iRandPick == 0) ? m_pBossA : m_pBossB;
        if (waitBoss->Get_CurStateType() != EBossStateType::Wait)
        {

        }*/
        //if (m_pBossA->Get_CurStateType() != EBossStateType::Wait)
        //{
        //    soloBoss = m_pBossA;
        //    //m_pBossB->ChangeState(new CBossWaitState);
        //}
        //else if (m_pBossB->Get_CurStateType() != EBossStateType::Wait)
        //{
        //    soloBoss = m_pBossB;
        //    //m_pBossA->ChangeState(new CBossWaitState);
        //}

        //int iRand = rand() % 4;

        /*if (soloBoss)
        {
            soloBoss->ChangeState(CreateTeamPattern(3));
            m_fSoloCooldown = 0.f;
        }*/

        if (iNum > 3)
        {
            int iRand = CRandomMgr::Get_Instance()->GetRandom(0, 3);
            if (soloBoss)
            {
                soloBoss->ChangeState(CreateTeamPattern(iRand));
                m_fSoloCooldown = 0.f;
            }
        }
        else
        {
            if (soloBoss)
            {
                soloBoss->ChangeState(CreateTeamPattern(iNum));
                m_fSoloCooldown = 0.f;
                iNum++;
            }
        }
        /*if (soloBoss)
        {
        soloBoss->ChangeState(CreateTeamPattern(iRand));
        m_fSoloCooldown = 0.f;
        }*/
    }
}
