#include "pch.h"
#include "CUIHealthBar.h"
#include "CBmpMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"

void CUIHealthBar::Initialize()
{
    m_tInfo.fX = 93.f;
    m_tInfo.fY = WINCY - 55.f;
    m_tInfo.fCX = 118.f;
    m_tInfo.fCY = 8.f;
    m_pFrameKey = L"hBar"; // 이미지 키
    m_eRender = RENDER_UI;
}

void CUIHealthBar::SetHP(int current, int max) {
    m_iCurrentHP = current;
    m_iMaxHP = max;
}

void CUIHealthBar::Render(HDC hDC)
{
    int curHp = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_HP();
    int maxHp = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MaxHP();

    if (curHp <= 0)
        return;

    float ratio = ((float)(curHp) / maxHp);
    int length = (int)(m_tInfo.fCX * ratio);

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    GdiTransparentBlt(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY,
        length, (int)m_tInfo.fCY, hMemDC, 0, 0,
        length, (int)m_tInfo.fCY, RGB(255, 220, 255));

    wchar_t szHpText[32] = {};
    swprintf_s(szHpText, L"%d / %d", curHp, maxHp);

    HFONT hFont = CreateFontW(
        -8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"./Image/Font/PF스타더스트.ttf"
    );

    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    int textW = 60;
    int textH = 12;

    int centerX = (int)(m_tInfo.fX + m_tInfo.fCX * 0.5f);
    int centerY = (int)(m_tInfo.fY + m_tInfo.fCY * 0.5f);

    RECT rcText = {
        centerX - textW / 2,
        centerY - textH / 2,
        centerX + textW / 2,
        centerY + textH / 2
    };

    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    DrawText(hDC, szHpText, -1, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
}

int CUIHealthBar::Update()
{
    return 0;
}

void CUIHealthBar::Late_Update()
{
}

void CUIHealthBar::Release()
{
}
