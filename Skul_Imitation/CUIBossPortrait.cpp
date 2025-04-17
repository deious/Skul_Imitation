#include "pch.h"
#include "CUIBossPortrait.h"
#include "CBmpMgr.h"

CUIBossPortrait::CUIBossPortrait()
{
}

CUIBossPortrait::~CUIBossPortrait()
{
}

void CUIBossPortrait::Initialize()
{
    m_tInfo.fX = 0.f;
    m_tInfo.fY = 0.f;
    m_tInfo.fCX = 800.f;
    m_tInfo.fCY = 100.f;
    m_pFrameKey = L"BossPortrait"; // 이미지 키
    m_eRender = RENDER_UI;
}

int CUIBossPortrait::Update()
{
    return 0;
}

void CUIBossPortrait::Late_Update()
{
}

void CUIBossPortrait::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    GdiTransparentBlt(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, hMemDC, 0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(255, 0, 255));
}

void CUIBossPortrait::Release()
{
}