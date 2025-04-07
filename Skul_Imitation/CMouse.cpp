#include "pch.h"
#include "CMouse.h"

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
}

int CMouse::Update()
{
	POINT		pt{};

	GetCursorPos(&pt);

	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;



	__super::Update_Rect();

	ShowCursor(false);

	return NOEVENT;
}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left, m_tRect.top,
		m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}
