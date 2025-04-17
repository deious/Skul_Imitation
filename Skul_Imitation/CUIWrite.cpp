#include "pch.h"
#include "CUIWrite.h"

CUIWrite::CUIWrite(float x, float y, float width, float height, const std::wstring& text, int fontSize)
    : m_sText(text), m_iFontSize(fontSize)
{
    m_tInfo.fX = x;
    m_tInfo.fY = y;
    m_tInfo.fCX = width;
    m_tInfo.fCY = height;
    m_eRender = RENDER_UI;
}

CUIWrite::~CUIWrite()
{
}

void CUIWrite::Initialize()
{
}

int CUIWrite::Update()
{
    return 0;
}

void CUIWrite::Late_Update()
{
}

void CUIWrite::Render(HDC hDC)
{
    RECT rc = {
        (LONG)m_tInfo.fX,
        (LONG)m_tInfo.fY,
        (LONG)(m_tInfo.fX + m_tInfo.fCX),
        (LONG)(m_tInfo.fY + m_tInfo.fCY)
    };

    // 글꼴 생성
    HFONT hFont = CreateFontW(
        -m_iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"./Image/Font/PF스타더스트.ttf"
    );
    //./Image/Font/PF스타더스트.ttf
    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    DrawText(hDC, m_sText.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
}

void CUIWrite::Release()
{
}

void CUIWrite::Set_Text(const std::wstring& text)
{
    m_sText = text;

}
