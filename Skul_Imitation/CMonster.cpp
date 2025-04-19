#include "pch.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CTileMgr.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CAttackCollider.h"
#include "CObj.h"
#include "CEffectMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Safe_Delete(m_pHitBox);
    Safe_Delete(m_pBehaviorTree);
}

void CMonster::Initialize()
{
    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 100.f;
    m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 30.f, 40.f);
    m_eRender = RENDER_GAMEOBJECT;
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 5;
    m_tFrame.iMotion = 0;
    m_fMoveSpeed = 60.f;
    m_iPrevMotion = MOTION_IDLE;
    m_fMoveDir = 0.f;

    m_bHit = false;
    m_bAttack = false;
    m_bWallCollision = false;
    m_bUseGravity = true;
    m_bIsDead = false;
    m_bDead = false;

    m_fMoveTimer = 0.f;
    m_fChangeDirTime = 0.f;
    m_fGravity = 0.f;
    m_fAttackTimer = 0.f;

    m_iDamage = 10;
    m_iHp = 50;
}

int CMonster::Update()
{
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

void CMonster::Late_Update()
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

void CMonster::Render(HDC hDC)
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
        RGB(255, 0, 255));

    if (CKeyMgr::Get_Instance()->Get_ShowAll())
    {
        m_pHitBox->Render(hDC);
    }
}

void CMonster::Release()
{
    Safe_Delete(m_pHitBox);
}

void CMonster::Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed)
{
    m_tFrame.iStart = iStart;
    m_tFrame.iEnd = iEnd;
    m_tFrame.iMotion = iMotion;
    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = dwSpeed;
}

void CMonster::Apply_Gravity()
{
    if (!m_bUseGravity)
        return;

    float landY = 0.f;
    bool onGround = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &landY);
    const float epsilon = 1.5f;

    if (onGround)
    {
        float dy = landY - m_tInfo.fY;

        if (fabs(dy) <= epsilon)
        {
            m_tInfo.fY = landY;
            m_fGravity = 0.f;
        }
        else if (dy > epsilon)
        {
            m_fGravity += GRAVITY_ACCEL;
            if (m_fGravity > GRAVITY_MAX)
                m_fGravity = GRAVITY_MAX;

            m_tInfo.fY += m_fGravity;
        }
        else
        {
            m_tInfo.fY = landY;
            m_fGravity = 0.f;
        }
    }
    else
    {
        m_fGravity += GRAVITY_ACCEL;
        if (m_fGravity > GRAVITY_MAX)
            m_fGravity = GRAVITY_MAX;

        m_tInfo.fY += m_fGravity;
    }
}

void CMonster::OnHit(CAttackCollider* pCol)
{
    m_iHp -= pCol->Get_Damage();

    if (m_iHp <= 0 && !m_bIsDead)
    {
        m_iHp = 0;
        m_bIsDead = true;
        m_bDead = true;
        Safe_Delete(m_pBehaviorTree);

        EffectInfo effect;
        effect.eType = EFFECT_TYPE::SKILLA;
        effect.sFramekey = L"Monster_Dead";
        effect.vOffset;
        effect.vSize = Vec2(150.f, 150.f); // ÀÌÆåÆ® Å©±â
        effect.iStartFrame = 0;
        effect.iEndFrame = 10;
        effect.iFrameSpeed = 50;
        effect.fScale = 1.f;
        effect.fRotation = 0.f;

        CEffectMgr::Get_Instance()->Add_Effect(effect, { m_tInfo.fX, m_tInfo.fY });
    }
}
