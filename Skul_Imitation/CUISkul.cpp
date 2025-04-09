#include "pch.h"
#include "CUISkul.h"
#include "CBmpMgr.h"

void CUISkul::Initialize()
{
    m_tInfo.fX = 55.f;
    m_tInfo.fY = WINCY - 100.f;
    m_tInfo.fCX = 45.f;
    m_tInfo.fCY = 45.f;
    m_pFrameKey = L"sIcon"; // 이미지 키
    m_eRender = RENDER_UI;
}

int CUISkul::Update()
{
	return 0;
}

void CUISkul::Late_Update()
{
}

void CUISkul::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    GdiTransparentBlt(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 0, 255));
}

void CUISkul::Release()
{
}
