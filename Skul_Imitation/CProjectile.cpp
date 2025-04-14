#include "pch.h"
#include "CProjectile.h"
#include "CBmpMgr.h"

CProjectile::CProjectile(Vec2 pos, Vec2 dir)
    : m_Pos(pos), m_Dir(dir.Normalize())
{
    m_tInfo.fX = pos.x;
    m_tInfo.fY = pos.y;
    m_tInfo.fCX = 30.f;
    m_tInfo.fCY = 30.f;
}

void CProjectile::Initialize()
{
    m_eRender = RENDER_GAMEOBJECT;
}

int CProjectile::Update()
{
    m_Elapsed += DELTA_TIME;
    if (m_Elapsed >= m_LifeTime)
    {
        m_bDead = true;
        return DEAD;
    }

    m_Pos = m_Pos + m_Dir * m_Speed * DELTA_TIME;
    m_tInfo.fX = m_Pos.x;
    m_tInfo.fY = m_Pos.y;

    Update_Rect();
    return 0;
}

void CProjectile::Render(HDC hDC)
{
    if (m_bDead) return;

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");            // 임시 이미지
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
        RGB(255, 0, 255)  // 투명색 지정
    );

}

void CProjectile::OnHit(CAttackCollider* pCol)
{
    m_bDead = true;
}

void CProjectile::Release() {}

void CProjectile::Late_Update()
{
}
