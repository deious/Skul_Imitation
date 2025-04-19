#include "pch.h"
#include "CTrigger.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"

CTrigger::CTrigger(RECT area, std::function<void()> onTrigger)
    : m_Area(area), m_bTriggered(false), m_OnTrigger(onTrigger)
{
    m_tInfo.fX = (area.left + area.right) * 0.5f;
    m_tInfo.fY = (area.top + area.bottom) * 0.5f;
    m_tInfo.fCX = (float)(area.right - area.left);
    m_tInfo.fCY = (float)(area.bottom - area.top);
    m_eRender = RENDER_UI;
}

CTrigger::~CTrigger()
{
}

void CTrigger::Initialize()
{
}

int CTrigger::Update()
{
    if (m_bTriggered) return DEAD;

    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    if (!pPlayer) return 0;

    RECT playerRect = *pPlayer->Get_Rect();
    RECT intersection;
    if (IntersectRect(&intersection, &m_Area, &playerRect)) {
        m_bTriggered = true;
        if (m_OnTrigger) m_OnTrigger();
    }

    return 0;
}

void CTrigger::Late_Update()
{
}

void CTrigger::Render(HDC hDC)
{
    if (CKeyMgr::Get_Instance()->Get_ShowAll())
    {
        POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

        RECT rc = {
            screen.x - (LONG)(m_tInfo.fCX * 0.5f),
            screen.y - (LONG)(m_tInfo.fCY * 0.5f),
            screen.x + (LONG)(m_tInfo.fCX * 0.5f),
            screen.y + (LONG)(m_tInfo.fCY * 0.5f)
        };

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hDC, &rc, hBrush);
        DeleteObject(hBrush);
    }
}

void CTrigger::Release()
{
}
