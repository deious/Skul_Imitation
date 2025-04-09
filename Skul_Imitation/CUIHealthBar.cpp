#include "pch.h"
#include "CUIHealthBar.h"
#include "CBmpMgr.h"

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
    // 배경 바
    //RECT bg = { (int)m_tInfo.fX, (int)m_tInfo.fY, (int)(m_tInfo.fX + 100), (int)(m_tInfo.fY + 10) };
    //FillRect(hDC, &bg, (HBRUSH)GetStockObject(DKGRAY_BRUSH));

    // 체력 바
    //float ratio = (float)m_iCurrentHP / m_iMaxHP;
    //RECT fg = { (int)m_tInfo.fX, (int)m_tInfo.fY, (int)(m_tInfo.fX + 100 * ratio), (int)(m_tInfo.fY + 10) };
    //FillRect(hDC, &fg, (HBRUSH)GetStockObject(RED_BRUSH));

    //// 텍스트
    //std::wstring hpText = std::to_wstring(m_iCurrentHP) + L" / " + std::to_wstring(m_iMaxHP);
    //TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY - 15, hpText.c_str(), (int)hpText.length());

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    GdiTransparentBlt(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 220, 255));
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
