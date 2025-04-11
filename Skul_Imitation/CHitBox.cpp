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

void CHitBox::Update_Rect()
{
    m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
    m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5f);
    m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
    m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}

const RECT& CHitBox::Get_Rect() const { return m_tRect; }

RECT& CHitBox::Get_Rect() { return m_tRect; }

POINT CHitBox::Get_Center() const
{
    return { (int)m_tInfo.fX, (int)m_tInfo.fY };
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