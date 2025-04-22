#include "pch.h"
#include "CNPC.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CBmpMgr.h"

void CNPC::Initialize() 
{
    //m_eRender = RENDER_UI;
    m_tInfo.fCX = 150.f;
    m_tInfo.fCY = 150.f;
    m_eRender = RENDER_PRIORITY;
    m_sFrameKey = L"Spider";
}

int CNPC::Update()
{
    if (!m_bActive)
        return 0;

    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    if (!pPlayer)
        return 0;

    float dx = pPlayer->Get_Info()->fX - m_tInfo.fX;
    float dy = pPlayer->Get_Info()->fY - m_tInfo.fY;
    float distSq = dx * dx + dy * dy;
    m_bPlayerInRange = distSq < 100.f * 100.f;

    if (m_bPlayerInRange && CKeyMgr::Get_Instance()->Key_Down('F'))
    {
        CPlayer* npPlayer = dynamic_cast<CPlayer*>(pPlayer);
        if (npPlayer)
        {
            npPlayer->Set_Awaken();
        }
    }

    return 0;
}

void CNPC::Late_Update() { __super::Update_Rect(); }

void CNPC::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_sFrameKey.c_str());
    /*if (!hMemDC)
        return;*/
    if (hMemDC)
    {
        BitBlt(hDC, 1250, 300, 150, 150, hMemDC, 0, 0, SRCCOPY); // 화면 100,100 위치 강제출력
    }

    //POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

    /*int drawX = screen.x - (int)(m_tInfo.fCX * 0.5f);
    int drawY = screen.y - (int)(m_tInfo.fCY * 0.5f);

    GdiTransparentBlt(hDC,
        drawX, drawY,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        hMemDC,
        0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        RGB(255, 0, 255));*/

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)(m_tInfo.fY));
    GdiTransparentBlt(
        hDC,
        screen.x - (int)(m_tInfo.fCX * 0.5f),
        screen.y - (int)(m_tInfo.fCY * 0.5f),
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        hMemDC,
        0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        RGB(255, 0, 255));

    if (m_bPlayerInRange)
    {
        RECT rcText = { screen.x - 60, screen.y - 80, screen.x + 60, screen.y - 60 };

        HFONT hFont = CreateFontW(
            -24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
            L"./Image/Font/PF스타더스트.ttf"
        );

        HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

        SetBkMode(hDC, TRANSPARENT);
        SetTextColor(hDC, RGB(255, 255, 255));
        DrawText(hDC, L"F: 각성하기", -1, &rcText, DT_CENTER | DT_SINGLELINE);

        SelectObject(hDC, hOldFont);
        DeleteObject(hFont);
    }
}

void CNPC::Release() {}

void CNPC::Set_Activate(bool b) { m_bActive = b; }

