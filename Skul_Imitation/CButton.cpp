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

	GdiTransparentBlt(hDC,/// ���� ���� dc
		m_tRect.left,		// ���� ���� ��ġ ��ǥ left
		m_tRect.top,					// ���� ���� ��ġ ��ǥ top
		(int)m_tInfo.fCX,				// ���� ���� ���� ������
		(int)m_tInfo.fCY,				// ���� ���� ���� ������
		hMemDC,							// ������ �̹��� dc
		m_iDrawId * (int)m_tInfo.fCX,
		0,								// ������ �̹����� left, top
		(int)m_tInfo.fCX,				// ������ �̹����� ����
		(int)m_tInfo.fCY,				// ������ �̹����� ����
		RGB(255, 255, 255));			// ������ �̹��� ���� ��
}

void CButton::Release()
{
}
