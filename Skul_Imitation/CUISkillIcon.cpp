#include "pch.h"
#include "CUISkillIcon.h"
#include "CBmpMgr.h"

CUISkillIcon::CUISkillIcon(float fX, float fY, const std::wstring& iconKey, const std::wstring& iconType)
{
    m_tInfo.fX = fX;
    m_tInfo.fY = fY;
    m_tInfo.fCX = 22.f;
    m_tInfo.fCY = 22.f;
    m_eRender = RENDER_UI;
    m_sIconKey = iconKey;
    m_sIconType = iconType;
    //m_pFrameKey = L"SNormalAIcon";
}

CUISkillIcon::~CUISkillIcon()
{
}

void CUISkillIcon::Initialize()
{
    m_eRender = RENDER_UI;
    //m_pFrameKey = L"SNormalAIcon";
}

int CUISkillIcon::Update()
{
    return 0;
}

void CUISkillIcon::Late_Update()
{
}

void CUISkillIcon::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_sIconKey.c_str());
    if (!hMemDC) return;

    GdiTransparentBlt(
        hDC,
        (int)(m_tInfo.fX), (int)(m_tInfo.fY),
        (int)(m_tInfo.fCX), (int)(m_tInfo.fCY),
        hMemDC,
        0, 0,
        (int)(m_tInfo.fCX), (int)(m_tInfo.fCY),
        RGB(255, 0, 255));
}

void CUISkillIcon::Release()
{
}

std::wstring CUISkillIcon::Get_IconType() const
{
    return m_sIconType;
}

void CUISkillIcon::Set_IconKey(const std::wstring& key)
{
    m_sIconKey = key;
}
