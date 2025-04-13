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

CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
    m_tInfo = { 700.f, WINCY >> 1, 128.f, 128.f };
    m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 30.f, 80.f);
    m_fSpeed = 3.f;
    m_fDistance = 100.f;
    //m_fVelocity = 20.f;
    m_iHp = 100;
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
        MessageBox(g_hWnd, L"보스 2번 생성", _T("Fail"), MB_OK);
        CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/Boss_2_2.bmp", L"Boss_2");
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
    BuildBehaviorTree();
}

int CBoss::Update()
{
    if (m_bDead)
        return DEAD;

    if (m_pAI)
        m_pAI->Run();

    if (m_pCurState)
        m_pCurState->Update(this);

    m_tInfo.fX += m_fSpeed * DELTA_TIME;

    __super::Update_Rect();
    /*m_HitBox.Set_Pos(m_tInfo.fX, m_tInfo.fY);*/
    return 0;
}

void CBoss::Late_Update()
{
    Apply_Gravity();
    //m_tInfo.fX += m_fSpeed * DELTA_TIME;
    m_pHitBox->Set_Pos(m_tInfo.fX - 15.f, m_tInfo.fY);
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

    wchar_t hpText[32];
    swprintf_s(hpText, L"HP: %d", m_iHp); // 보스 체력

    TextOut(hDC,
        screenPos.x,
        screenPos.y - 50,
        hpText,
        (int)wcslen(hpText)
    );

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
}

void CBoss::ChangeState(IState<CBoss>* pNewState)
{
    if (m_pCurState)
        m_pCurState->Exit(this);

    delete m_pCurState;
    m_pCurState = pNewState;

    if (m_pCurState)
        m_pCurState->Enter(this);
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

    m_pAI = new ActionNode([this]() {
        static float elapsed = 0.f;
        elapsed += DELTA_TIME;

        if (elapsed >= 5.0f)
        {
            elapsed = 0.f;

            int randPattern = rand() % 3;

            switch (randPattern)
            {
            case 0:
                this->ChangeState(new CBossDuoDashFromEdge());
                break;
            case 1:
                this->ChangeState(new CBossDuoDive());
                break;
            case 2:
                this->ChangeState(new CBossDashAttack());
                break;
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

bool CBoss::IsAwakened() const
{
    return false;
}

bool CBoss::IsDead() const
{
    return false;
}

bool CBoss::ShouldSyncAttack() const
{
    return false;
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

void CBoss::Set_ID(int id)
{
    m_iBossID = id;
}

void CBoss::Set_Speed(float fSpeed)
{
    m_fSpeed = fSpeed;
}

void CBoss::Set_PairBoss(CBoss* pOther)
{
    m_pPairBoss = pOther;
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

void CBoss::OnHit(CAttackCollider* pCol)
{
    m_dwHitTime = GetTickCount64();
    m_bShowHitText = true;
    int damage = pCol->Get_Damage();

    // 체력 감소
    m_iHp -= damage;

    /*if (m_iHp <= 0)
        ChangeState(EState::Die);
    else
        ChangeState(EState::Hit);*/
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
