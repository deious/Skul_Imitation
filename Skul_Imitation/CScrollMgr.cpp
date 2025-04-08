#include "pch.h"
#include "CScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fScrollY(0.f)
{
}

CScrollMgr::~CScrollMgr()
{
}

float CScrollMgr::Get_ScrollX() { return m_fScrollX; }
float CScrollMgr::Get_ScrollY() { return m_fScrollY; }

void CScrollMgr::Set_ScrollX(float fX) { m_fScrollX += fX; }
void CScrollMgr::Set_ScrollY(float fY) { m_fScrollY += fY; }

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - 1920 > m_fScrollX)
		m_fScrollX = WINCX - 1920;

	if (WINCY - 1280 > m_fScrollY)
		m_fScrollY = WINCY - 1280;

}

CScrollMgr* CScrollMgr::Get_Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CScrollMgr;
	}

	return m_pInstance;
}

void CScrollMgr::Destroy_Instance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
