#include "pch.h"
#include "CLightningProjectile.h"
#include "CAttackCollider.h"
#include "CObjMgr.h"

CLightningProjectile::CLightningProjectile(Vec2 pos, Vec2 dir)
    : CProjectile(pos, dir)
{
    m_tInfo.fCX = 96.f;
    m_tInfo.fCY = 31.f;
    m_fSpeed = 100.f;
    CAttackCollider* pCol = new CAttackCollider(
        this,
        m_tInfo.fX, m_tInfo.fY,
        60.f, 30.f,     // width, height
        0.f, 2.f,       // delay, duration
        CAttackCollider::ColliderType::Follow,
        ETeam::Enemy,
        ESkillType::Attack,
        20
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
}

int CLightningProjectile::Update()
{
    if (m_bDead)
        return DEAD;

    m_tInfo.fX += m_Dir.x * m_fSpeed * DELTA_TIME;
    m_tInfo.fY += m_Dir.y * m_fSpeed * DELTA_TIME;

    m_tInfo.fX = m_Pos.x;
    m_tInfo.fY = m_Pos.y;
    __super::Update();

    return 0;
}

void CLightningProjectile::Render(HDC hDC)
{
    if (m_bDead) return;

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"temp2");
    if (!hMemDC) return;

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

    GdiTransparentBlt(
        hDC,
        screen.x - (int)(m_tInfo.fCX * 0.5f),
        screen.y - (int)(m_tInfo.fCY * 0.5f),
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        0, 0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)
    );
}

void CLightningProjectile::OnHit(CAttackCollider* pCol)
{
	m_bDead = true;
}
