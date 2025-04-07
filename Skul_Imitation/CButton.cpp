#include "pch.h"
#include "CButton.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CButton::CButton() : m_iDrawId(0)
{
}

CButton::~CButton()
{
	Release();
}

void CButton::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");

	m_eRender = RENDER_UI;
}

int CButton::Update()
{

	__super::Update_Rect();

	return NOEVENT;
}

void CButton::Late_Update()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_STAGE);

			else if (!lstrcmp(L"Edit", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_EDIT);

			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawId = 1;
	}

	else
		m_iDrawId = 0;
}

void CButton::Render(HDC hDC)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left,		// 복사 받을 위치 좌표 left
		m_tRect.top,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		m_iDrawId * (int)m_tInfo.fCX,
		0,								// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 255, 255));			// 제거할 이미지 색상 값
}

void CButton::Release()
{
}
