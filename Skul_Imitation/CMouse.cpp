#include "pch.h"
#include "CMouse.h"
#include "CObjMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_eRender = RENDER_MOUSE;
}

int CMouse::Update()
{
	/*OutputDebugString(L"[Mouse] Update called\n");*/
	POINT		pt{};

	GetCursorPos(&pt);

	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	/*wchar_t szBuf[128];
	swprintf_s(szBuf, L"[Mouse Update] fX: %.2f, fY: %.2f\n", m_tInfo.fX, m_tInfo.fY);
	OutputDebugString(szBuf);*/

	__super::Update_Rect();

	//ShowCursor(false);
	return NOEVENT;
}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC hDC)
{
	/*wchar_t szBuf[128];
	swprintf_s(szBuf, L"[Mouse Render] Left: %d, Top: %d, Right: %d, Bottom: %d\n",
		m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	OutputDebugString(szBuf);*/

	Ellipse(hDC,
		m_tRect.left, m_tRect.top,
		m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}
