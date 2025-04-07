#include "pch.h"
#include "CTile.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

CTile::CTile() : m_iDrawID(0), m_iOption(0)
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECX;
}

int CTile::Update()
{


	__super::Update_Rect();

	return 0;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");

	int		iScrollX = (INT)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (INT)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		TILECX, TILECY,
		hMemDC,
		m_iDrawID * TILECX,
		0,
		SRCCOPY);
}

void CTile::Release()
{
}
