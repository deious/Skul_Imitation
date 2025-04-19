#include "pch.h"
#include "CArcherMonster.h"
#include "CObjMgr.h"
#include "CTileMgr.h"
#include "CCollisionMgr.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CAttackCollider.h"
#include "CArrow.h"

CArcherMonster::CArcherMonster()
{
}

CArcherMonster::~CArcherMonster()
{
}

void CArcherMonster::Attack()
{
    if (m_bAttack) return;

    m_bAttack = true;
    m_iPrevMotion = MOTION_ATTACK;
    //m_pFrameKey = (m_eDir == DIR_LEFT) ? L"Archer_Left" : L"Archer_Right";
    Set_Frame(0, 3, 2, 300);

    Vec2 monsterPos(this->Get_Info()->fX, this->Get_Info()->fY);
    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    Vec2 playerPos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
    Vec2 dir = {playerPos.x - monsterPos.x, 0.f};
    dir.Normalize();

    /*wchar_t szLog[128];
    swprintf_s(szLog, L"[DIR] dir.x = %.2f, dir.y = %.2f\n", dir.x, dir.y);
    OutputDebugString(szLog);*/

    m_pFrameKey = dir.x > 0 ? L"Archer_Right" : L"Archer_Left";

    CObj* pProj = new CArrow(monsterPos, dir, this);
    pProj->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_PROJECTILE, pProj);

    /*CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    Vec2 playerPos(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
    Vec2 dir = playerPos - firePos;
    dir.Normalize();

    CObj* pProj = new CLightningProjectile(firePos, dir, pBoss->Get_ID());
    pProj->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_PROJECTILE, pProj);*/
}

void CArcherMonster::MoveRandom()
{
    if (m_bHit || m_bAttack) return;
    if (m_iPrevMotion != MOTION_WALK)
    {
        Set_Frame(0, 5, 1, 80);
        m_iPrevMotion = MOTION_WALK;
    }

    m_fMoveTimer += DELTA_TIME;
    if (m_fMoveTimer >= m_fChangeDirTime)
    {
        m_fMoveDir = (rand() % 2 == 0) ? -1.f : 1.f;
        m_fChangeDirTime = 2.f + static_cast<float>(rand()) / RAND_MAX * 2.f;
        m_fMoveTimer = 0.f;
    }

    if (m_bWallCollision)
    {
        m_fMoveDir *= -1.f;
        m_bWallCollision = false;
    }

    m_eDir = (m_fMoveDir < 0) ? DIR_LEFT : DIR_RIGHT;
    m_pFrameKey = (m_eDir == DIR_LEFT) ? L"Archer_Left" : L"Archer_Right";
}

void CArcherMonster::BuildBehaviorTree()
{
    auto* root = new SelectorNode();

    auto* attackSeq = new SequenceNode();
    attackSeq->AddChild(new ConditionNode([this]() {
        if (m_fSpawnTime < m_fAttackDelayAfterSpawn)
            return false;

        CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
        if (!pPlayer) return false;

        if (m_bAttack) return false;

        float dx = pPlayer->Get_Info()->fX - m_tInfo.fX;
        float dy = pPlayer->Get_Info()->fY - m_tInfo.fY;

        isInHorizontalRange = fabsf(dx) <= attackRange;
        isOnSameLine = fabsf(dy) <= verticalTolerance;
        return isInHorizontalRange && isOnSameLine;
        }));
    attackSeq->AddChild(new ActionNode([this]() {
        this->Attack();
        }));

    root->AddChild(attackSeq);
    root->AddChild(new ActionNode([this]() {
        this->MoveRandom();
        }));

    m_pBehaviorTree = root;
}

void CArcherMonster::Initialize()
{
    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 100.f;
    m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 30.f, 40.f);
    m_eRender = RENDER_GAMEOBJECT;
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 5;
    m_tFrame.iMotion = 0;
    m_fMoveSpeed = 60.f;
    m_pFrameKey = L"Archer_Left";
    m_iPrevMotion = MOTION_IDLE;
    m_fMoveDir = 0.f;
    BuildBehaviorTree();
}

int CArcherMonster::Update()
{
    m_fSpawnTime += DELTA_TIME;

    if (m_bDead)
        return DEAD;

    if (m_pBehaviorTree)
        m_pBehaviorTree->Run();

    if (m_bAttack)
    {
        m_fAttackTimer += DELTA_TIME;
        if (m_fAttackTimer >= 1.2f)
        {
            m_bAttack = false;
            m_fAttackTimer = 0.f;
        }
    }

    __super::Update_Rect();
    Move_Frame();

    return 0;
}

void CArcherMonster::Late_Update()
{
    Apply_Gravity();
    if (!m_bHit && !m_bAttack)
    {
        m_tInfo.fX += m_fMoveDir * m_fMoveSpeed * DELTA_TIME;
    }

    m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);
    m_pHitBox->Update_Rect();
    CCollisionMgr::PlayerToTile(this, CTileMgr::Get_Instance()->Get_Tree());
}

void CArcherMonster::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

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
        m_pHitBox->Render(hDC);
        POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

        RECT rc = {
            screen.x - (LONG)(m_tInfo.fCX * 0.5f),
            screen.y - (LONG)(m_tInfo.fCY * 0.5f),
            screen.x + (LONG)(m_tInfo.fCX * 0.5f),
            screen.y + (LONG)(m_tInfo.fCY * 0.5f)
        };

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
        FrameRect(hDC, &rc, hBrush);
        DeleteObject(hBrush);
    }
}

void CArcherMonster::Release()
{
    Safe_Delete(m_pHitBox);
}
