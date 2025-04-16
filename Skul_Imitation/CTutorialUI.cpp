#include "pch.h"
#include "CTutorialUI.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CTutorialUI::CTutorialUI()
{
}

CTutorialUI::CTutorialUI(const wstring& imgKey, const wstring& text, float x, float y)
{
}

void CTutorialUI::Initialize()
{
    m_tInfo.fCX = 32.f;
    m_tInfo.fCY = 32.f;

    m_pFrameKey = L"ABtn";
    m_text = L"test";
    m_eRender = RENDER_UI;

    /*CObj* pButton = CAbstractFactory<CTutorialUI>::Create_Obj(200.f, 400.f);
    pButton->Set_FrameKey(L"ABtn");
    CObjMgr::Get_Instance()->Add_Object(OBJ_TUTORIAL, pButton);

    pButton = CAbstractFactory<CTutorialUI>::Create_Obj(400.f, 400.f);
    pButton->Set_FrameKey(L"ABtn");
    CObjMgr::Get_Instance()->Add_Object(OBJ_TUTORIAL, pButton);

    pButton = CAbstractFactory<CTutorialUI>::Create_Obj(600.f, 400.f);
    pButton->Set_FrameKey(L"ABtn");
    CObjMgr::Get_Instance()->Add_Object(OBJ_TUTORIAL, pButton);*/
}

int CTutorialUI::Update()
{
	return 0;
}

void CTutorialUI::Render(HDC hDC)
{
    if (!m_bVisible)
        return;

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);
    int drawX = screenPos.x - (int)(m_tInfo.fCX * 0.5f);
    int drawY = screenPos.y - (int)(m_tInfo.fCY * 0.5f);

    if (hMemDC)
    {

        /*GdiTransparentBlt(hDC,
            m_tRect.left,
            m_tRect.top,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            0,
            0,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            RGB(255, 0, 255)
        );*/

        GdiTransparentBlt(hDC,
            drawX,
            drawY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            0,
            0,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            RGB(255, 0, 255)
        );
    }

    //GdiTransparentBlt(hDC,/// 복사 받을 dc
    //    m_tRect.left,		// 복사 받을 위치 좌표 left
    //    m_tRect.top,					// 복사 받을 위치 좌표 top
    //    (int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
    //    (int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
    //    hMemDC,							// 복사할 이미지 dc
    //    m_iDrawId * (int)m_tInfo.fCX,
    //    0,								// 복사할 이미지의 left, top
    //    (int)m_tInfo.fCX,				// 복사할 이미지의 가로
    //    (int)m_tInfo.fCY,				// 복사할 이미지의 세로
    //    RGB(255, 255, 255));			// 제거할 이미지 색상 값

    // 텍스트
    HFONT hFont = CreateFontW(
        24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"./Image/Font/PF스타더스트.ttf"
    );

    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkMode(hDC, TRANSPARENT);
    TextOut(hDC, drawX + 50, drawY + 5, m_text.c_str(), (int)m_text.length());
    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
    //TextOut(hDC, drawX + 10.f, drawY, m_text.c_str(), (int)m_text.length());
}

void CTutorialUI::Set_Visible(bool bVisible)
{
}

void CTutorialUI::Late_Update()
{
}

void CTutorialUI::Release()
{
}

void CTutorialUI::Set_Text(const wstring& text)
{
    m_text = text;
}
