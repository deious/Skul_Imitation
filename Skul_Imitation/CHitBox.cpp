#include "pch.h"
#include "CHitBox.h"
#include "CKeyMgr.h"

CHitBox::CHitBox() : m_tInfo({ 0.f, 0.f, 0.f, 0.f })
{
    Update_Rect();
}

CHitBox::CHitBox(float x, float y, float cx, float cy)
{
    m_tInfo = { x, y, cx, cy };
    Update_Rect();
}

void CHitBox::Set_Pos(float x, float y)
{
    m_tInfo.fX = x;
    m_tInfo.fY = y;
    Update_Rect();
}

void CHitBox::Set_Size(float cx, float cy)
{
    m_tInfo.fCX = cx;
    m_tInfo.fCY = cy;
    Update_Rect();
}

void CHitBox::Set_LastHitFrame(DWORD frame) { m_dwLastHitFrame = frame; }

void CHitBox::Set_MaxHits(int iMaxHits) { m_iMaxHits = iMaxHits; }

void CHitBox::Reset_HitCount() { m_iHitCount = 0; }

void CHitBox::Update_Rect()
{
    float fx = m_tInfo.fX + m_vOffset.x;
    float fy = m_tInfo.fY + m_vOffset.y;

    m_tRect.left = LONG(fx - m_tInfo.fCX * 0.5f);
    m_tRect.top = LONG(fy - m_tInfo.fCY * 0.5f);
    m_tRect.right = LONG(fx + m_tInfo.fCX * 0.5f);
    m_tRect.bottom = LONG(fy + m_tInfo.fCY * 0.5f);

    /*m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
    m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5f);
    m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
    m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);*/
}

void CHitBox::Set_Offset(float x, float y)
{
    m_vOffset = { x, y };
    Update_Rect();
}

const RECT& CHitBox::Get_Rect() const { return m_tRect; }

RECT& CHitBox::Get_Rect() { return m_tRect; }

POINT CHitBox::Get_Center() const
{
    return { (int)m_tInfo.fX, (int)m_tInfo.fY };
}
DWORD CHitBox::Get_LastHitFrame() const
{
    return m_dwLastHitFrame;
}


void CHitBox::Render(HDC hDC)
{
    if (!CKeyMgr::Get_Instance()->Get_ShowAll())
        return;

    RECT drawRc = CCameraMgr::Get_Instance()->WorldToScreenRect(m_tRect);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
    FrameRect(hDC, &drawRc, hBrush);
    DeleteObject(hBrush);
}

int CHitBox::Get_MaxHit() const
{
    return m_iMaxHits;
}

void CHitBox::Add_Hit() { ++m_iHitCount; }

bool CHitBox::Can_Hit() const { return m_iHitCount < m_iMaxHits; }
