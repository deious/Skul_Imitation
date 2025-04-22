#include "pch.h"
#include "CBoss.h"
#include "CBmpMgr.h"
#include "IState.h"
#include "CBossAttackState.h"
#include "CBossIdleState.h"
#include "CLineMgr.h"
#include "CCameraMgr.h"
#include "CCollisionMgr.h"
#include "CTileMgr.h"
#include "CKeyMgr.h"
#include "CBossDuoDashFromEdge.h"
#include "CBossDuoDive.h"
#include "CBossDashAttack.h"
#include "CBossDuoShootingLightning.h"
//#include "CBossStage.cpp"
#include "CBossWaitState.h"
#include "CBossAwakenState.h"
#include "CRandomMgr.h"
#include "CBossDieState.h"
#include "CTimeMgr.h"

CBoss::CBoss()
{
    m_pCurState = nullptr;
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
    m_tInfo = { 700.f, WINCY >> 1, 128.f, 128.f };
    m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 30.f, 80.f);
    //m_pHitBox->Set_Offset(0.f, -20.f);
    m_fSpeed = 3.f;
    m_fDistance = 100.f;
    //m_fVelocity = 20.f;
    m_iHp = m_iMaxHp;
    m_bDead = false;
    // 보스 생성전 id set 해줘야 함
    m_eRender = RENDER_GAMEOBJECT;
    if (m_iBossID == 0)
    {
        CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/Boss_2_1.bmp", L"Boss_1");
        m_pFrameKey = L"Boss_1";
    }
    else
    {
        //MessageBox(g_hWnd, L"보스 2번 생성", _T("Fail"), MB_OK);
        CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/Boss_2_1.bmp", L"Boss_2");
        m_pFrameKey = L"Boss_2";
    }

    //CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/Boss_2_Awaken.bmp", L"Boss_Awaken");

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 7;
    m_tFrame.iMotion = 0;

    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = 200;
    //m_pFrameKey = L"Boss_1";
    m_dwHitTime = GetTickCount64();
    ChangeState(new CBossIdleState());
    //BuildBehaviorTree();
}

int CBoss::Update()
{
    if (m_pCurState)
        m_pCurState->Update(this);

    if (m_bDead)
        return DEAD;

    //CheckAndUpdateBehaviorTree();

    /*if (m_pAI)
        m_pAI->Run();*/

    /*if (m_pCurState)
        m_pCurState->Update(this);*/

    m_tInfo.fX += m_fSpeed * DELTA_TIME;
    if (m_tInfo.fX < 100.f)
    {
        m_tInfo.fX = 100.f;
    }
    else if (m_tInfo.fX > 700.f)
    {
        m_tInfo.fX = 700.f;
    }

    __super::Update_Rect();
    Move_Frame();
    /*m_HitBox.Set_Pos(m_tInfo.fX, m_tInfo.fY);*/
    return 0;
}

void CBoss::Late_Update()
{
    Apply_Gravity();
    //m_tInfo.fX += m_fSpeed * DELTA_TIME;
    m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);
    m_pHitBox->Update_Rect();
    //__super::Update_Rect();
    CCollisionMgr::PlayerToTile(this, CTileMgr::Get_Instance()->Get_Tree());
}

void CBoss::Render(HDC hDC)
{
    m_pHitBox->Render(hDC);
    /*if (m_eDir == EDirection::LEFT)
        m_pFrameKey = L"Player_LEFT";
    else
        m_pFrameKey = L"Player_RIGHT";*/

    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

    //wchar_t hpText[32];
    //swprintf_s(hpText, L"HP: %d", m_iHp); // 보스 체력

    //TextOut(hDC,
    //    screenPos.x,
    //    screenPos.y - 50,
    //    hpText,
    //    (int)wcslen(hpText)
    //);

    int drawX = screenPos.x - (int)(m_tInfo.fCX * 0.5f);
    int drawY = screenPos.y - (int)(m_tInfo.fCY * 0.5f);


    GdiTransparentBlt(hDC,
        drawX,
        drawY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        m_tFrame.iStart * (int)m_tInfo.fCX,
        m_tFrame.iMotion * (int)m_tInfo.fCY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)
    );

    /*else
    {
        GdiTransparentBlt(hDC,
            drawX,
            drawY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            m_tFrame.iStart * (int)m_tInfo.fCX,
            m_tFrame.iMotion * (int)m_tInfo.fCY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            RGB(0, 0, 0)
        );
    }*/

    if (CKeyMgr::Get_Instance()->Get_ShowAll())
    {
        POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

        RECT rc = {
            screen.x - (LONG)(m_tInfo.fCX * 0.5f),
            screen.y - (LONG)(m_tInfo.fCY * 0.5f),
            screen.x + (LONG)(m_tInfo.fCX * 0.5f),
            screen.y + (LONG)(m_tInfo.fCY * 0.5f)
        };

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));  // 초록색
        FrameRect(hDC, &rc, hBrush);
        DeleteObject(hBrush);

        if (GetTickCount64() - m_dwHitTime < 1000)
        {
            if (m_bShowHitText)
            {
                POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY - 80);
                TextOut(hDC, screen.x, screen.y, L"보스 맞았음!", lstrlen(L"보스 히트"));
                m_bShowHitText = false;
            }
        }
    }
}

void CBoss::Release()
{
    Safe_Delete(m_pHitBox);
    Safe_Delete(m_pCurState);
    m_pCurState = nullptr;
    m_pPairBoss = nullptr;
}

void CBoss::ChangeState(IState<CBoss>* pNewState)
{
    /*if (IsDead() || m_pCurState == nullptr)
        return;*/

    if (IsDead())
        return;

    if (m_pCurState)
        m_pCurState->Exit(this);

    delete m_pCurState;
    m_pCurState = pNewState;

    if (m_pCurState)
        m_pCurState->Enter(this);

    /*if (IsCheck())
        Set_Dead();*/
}

void CBoss::BuildBehaviorTree()
{
    //static float fTimer = 0.f;

    //m_pAI = new ActionNode([this]() {
    //    static float elapsed = 0.f;
    //    elapsed += DELTA_TIME;

    //    if (elapsed >= 5.0f)
    //    {
    //        elapsed = 0.f;
    //        //this->ChangeState(new CBossDuoDashFromEdge());
    //        //this->ChangeState(new CBossDuoDive());
    //        this->ChangeState(new CBossDashAttack());
    //    }

    //    return true;
    //    });

    //m_pAI = new ActionNode([this]() {
    //    static float elapsed = 0.f;
    //    elapsed += DELTA_TIME;

    //    if (elapsed >= 5.0f)
    //    {
    //        elapsed = 0.f;

    //        int randPattern = rand() % 4;

    //        switch (randPattern)
    //        {
    //        case 0:
    //            this->ChangeState(new CBossDuoDashFromEdge());
    //            //this->ChangeState(new CBossDuoShootingLightning());
    //            break;
    //        case 1:
    //            this->ChangeState(new CBossDuoDive());
    //            //this->ChangeState(new CBossDuoShootingLightning());
    //            break;
    //        case 2:
    //            this->ChangeState(new CBossDashAttack());
    //            //this->ChangeState(new CBossDuoShootingLightning());
    //            break;
    //        case 3:
    //            this->ChangeState(new CBossDuoShootingLightning());
    //            break;
    //        }
    //    }

    //    return true;
    //    });

    m_pAI = new ActionNode([this]() {
        static float fTeamTimer = 0.f;
        static float fSoloTimer = 0.f;

        fTeamTimer += DELTA_TIME;
        fSoloTimer += DELTA_TIME;

        CBoss* pair = m_pPairBoss;

        // 팀 패턴 실행
        if (m_iBossID == 0 && fTeamTimer >= 10.f)
        {
            fTeamTimer = 0.f;

            int randPattern = rand() % 3;
            switch (randPattern)
            {
            case 0:
                this->ChangeState(new CBossDuoDashFromEdge());
                if (pair) pair->ChangeState(new CBossDuoDashFromEdge());
                break;
            case 1:
                this->ChangeState(new CBossDuoDive());
                if (pair) pair->ChangeState(new CBossDuoDive());
                break;
            case 2:
                this->ChangeState(new CBossDuoShootingLightning());
                if (pair) pair->ChangeState(new CBossDuoShootingLightning());
                break;
            }

            // 둘 중 한 명 대기
            if (pair)
            {
                int pick = rand() % 2;
                if (pick == 0)
                    this->ChangeState(new CBossWaitState());
                else
                    pair->ChangeState(new CBossWaitState());
            }
        }

        // 단독 패턴 (각 보스 개별로 수행)
        if (fSoloTimer >= 2.f)
        {
            fSoloTimer = 0.f;

            if (m_pCurState && m_pCurState->GetType() != EBossStateType::Wait)
            {
                this->ChangeState(new CBossDashAttack());
            }
        }

        return true;
        });

    //m_fAITimer = 0.f;

    //m_pAI = new ActionNode([this]() {
    //    m_fAITimer += DELTA_TIME;

    //    if (m_fAITimer >= 2.0f)
    //    {
    //        m_fAITimer = 0.f;
    //        this->ChangeState(new CBossAttackState());
    //    }

    //    return true;
    //    });
}

void CBoss::BuildSoloBehaviorTree()
{
    if (m_pAI)
        m_pAI = nullptr;

    SequenceNode* pRoot = new SequenceNode();

    SelectorNode* pAwakenOnlyOnce = new SelectorNode();
    SequenceNode* pAwakenSeq = new SequenceNode();

    pAwakenSeq->AddChild(new ActionNode([this]() {
        if (!this->IsAwakened())
        {
            this->ChangeState(new CBossAwakenState());
            this->Set_AnimStatus(false);
            return false;
        }
        return true;
        }));

    pAwakenSeq->AddChild(new ConditionNode([this]() {
        return this->Is_AnimFinished();
        }));

    pAwakenSeq->AddChild(new ActionNode([this]() {
        m_bAwakened = true;
        return true;
        }));

    pAwakenOnlyOnce->AddChild(pAwakenSeq);

    SelectorNode* pRandomSelector = new SelectorNode();

    pRandomSelector->AddChild(new ActionNode([this]() {
        int iRand = CRandomMgr::Get_Instance()->GetRandom(0, 3);
        this->Set_AnimFinish();

        switch (iRand)
        {
        case 0: this->ChangeState(new CBossDashAttack()); break;
        case 1: this->ChangeState(new CBossDuoDashFromEdge()); break;
        case 2: this->ChangeState(new CBossDuoShootingLightning()); break;
        case 3: this->ChangeState(new CBossDuoDive()); break;
        }
        return false;
        }));

    pRandomSelector->AddChild(new ConditionNode([this]() {
        return this->Is_AnimFinished();
        }));

    pRoot->AddChild(pAwakenOnlyOnce);
    pRoot->AddChild(pRandomSelector);

    m_pAI = pRoot;
}

bool CBoss::IsAwakened() const
{
    return m_bAwakened;
}

bool CBoss::IsDead() const
{
    return m_bDead;
}

bool CBoss::ShouldSyncAttack() const
{
    return false;
}

void CBoss::OnHit(int damage)
{
    m_iHp -= damage;

    if (m_iHp <= 0 && !m_bIsDead)
    {
        m_iHp = 0;
        m_bIsDead = true;
        ChangeState(new CBossDieState());
    }
}

void CBoss::Recovery()
{
    m_iHp = m_iMaxHp;
}

int CBoss::Get_ID()
{
    return m_iBossID;
}

float CBoss::Get_Speed()
{
    return m_fSpeed;
}

CBoss* CBoss::Get_PairBoss() const
{
    return m_pPairBoss;
}

bool CBoss::IsCheck() const
{
    return m_bIsDead;
}

void CBoss::Set_ID(int id)
{
    m_iBossID = id;
}

void CBoss::Set_Speed(float fSpeed)
{
    m_fSpeed = fSpeed;
}

EBossStateType CBoss::Get_CurStateType() const
{
    if (m_pCurState == nullptr)
        return EBossStateType::None;        // 여긴 아님

    if (m_pCurState)
        return m_pCurState->GetType();
    return EBossStateType::None;
}

int CBoss::Get_Hp()
{
    return m_iHp;
}

void CBoss::Set_PairBoss(CBoss* pOther)
{
    m_pPairBoss = pOther;
}

int CBoss::Get_MaxHp()
{
    return m_iMaxHp;
}

void CBoss::Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed)
{
    m_tFrame.iStart = iStart;
    m_tFrame.iEnd = iEnd;
    m_tFrame.iMotion = iMotion;
    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = dwSpeed;
}

void CBoss::Set_FrameKey(const TCHAR* pKey)
{
    m_pFrameKey = pKey;
}

void CBoss::Set_Gravity()
{
    m_bUseGravity = !m_bUseGravity;
}

void CBoss::Set_Invincibility(bool b)
{
    m_binvincibility = b;
}

void CBoss::Set_Controller(CBossController* pController)
{
    m_pController = pController;
}

CBossController* CBoss::Get_Controller() const
{
    return m_pController;
}

void CBoss::OnHit(CAttackCollider* pCol)
{
    m_dwHitTime = GetTickCount64();
    m_bShowHitText = true;
    if (!m_binvincibility)
        m_iHp -= pCol->Get_Damage();

    if (m_iHp <= 0 && !m_bIsDead)
    {
        m_iHp = 0;
        m_bIsDead = true;
        ChangeState(new CBossDieState());
        //m_bDead = true;
        //ChangeState(nullptr);  // 상태 제거
        //Safe_Delete(m_pAI);    // 행동 트리 제거
    }
}

void CBoss::CheckAndUpdateBehaviorTree()
{
    if (m_pPairBoss && m_pPairBoss->IsDead() && m_bUseTeamTree)
    {
        m_bUseTeamTree = false;
        BuildSoloBehaviorTree();  // 트리 변경
    }
}

void CBoss::Apply_Gravity()
{
    if (!m_bUseGravity)
        return;

    float landY = 0.f;
    bool onGround = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &landY);

    if (!onGround || m_tInfo.fY < landY)
    {
        m_fGravity += GRAVITY_ACCEL;
        if (m_fGravity > GRAVITY_MAX)
            m_fGravity = GRAVITY_MAX;

        m_tInfo.fY += m_fGravity;
    }
    else
    {
        m_fGravity = 0.f;
        m_tInfo.fY = landY;
    }
}

bool CBoss::Move_Frame()
{
    WCHAR szLog[128];

    // 현재 프레임 상태 로그
    swprintf_s(szLog, L"[Move_Frame] 현재 프레임: %d / %d, 시간: %llu / %llu\n",
        m_tFrame.iStart, m_tFrame.iEnd, m_tFrame.dwTime + m_tFrame.dwFrameSpeed, GetTickCount64());
    OutputDebugStringW(szLog);
    if (m_tFrame.dwTime + m_tFrame.dwFrameSpeed < GetTickCount64())
    {
        ++m_tFrame.iStart;
        m_tFrame.dwTime = GetTickCount64();
        swprintf_s(szLog, L"[Move_Frame] 프레임 증가됨 → iStart: %d\n", m_tFrame.iStart);
        OutputDebugStringW(szLog);
        if (m_tFrame.iStart > m_tFrame.iEnd)
        {
            m_tFrame.iStart = 0;
            m_bAnimed = true;

            OutputDebugStringW(L"[Move_Frame] 애니메이션 종료 → m_bAnimed = true\n");
            return true;
        }
    }

    return false;
}

void CBoss::Set_AnimFinish()
{
    m_bAnimed = false;
}

bool CBoss::Is_AnimFinished()
{
    return m_bAnimed;
}

bool CBoss::Set_AnimStatus(bool state)
{
    return m_bAnimed = state;
}

void CBoss::Set_Awaken()
{
    m_bAwakened = true;
}
