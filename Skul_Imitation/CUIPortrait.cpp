#include "pch.h"
#include "CUIPortrait.h"

void CUIPortrait::Initialize()
{
    m_tInfo.fX = 50.f;
    //m_tInfo.fX = 200.f;
    m_tInfo.fY = WINCY - 100.f;
    m_tInfo.fCX = 168.f;
    m_tInfo.fCY = 66.f;
    m_pFrameKey = L"pFrame"; // 이미지 키
    m_eRender = RENDER_UI;
}

void CUIPortrait::Render(HDC hDC) 
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    GdiTransparentBlt(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 0, 255));
}

int CUIPortrait::Update()
{
    return 0;
}

void CUIPortrait::Late_Update()
{
}

void CUIPortrait::Release()
{
}
