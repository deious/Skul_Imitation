#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END), m_bDead(false), m_fDistance(0.f), m_fAngle(0.f)
, m_pTarget(nullptr), m_pFrameKey(L""), m_eRender(RENDER_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

const INFO* CObj::Get_Info() { return &m_tInfo; }
const RECT* CObj::Get_Rect() { return &m_tRect; }
bool CObj::Get_Dead() { return m_bDead; }

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}
void CObj::Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
void CObj::Set_Dead() { m_bDead = true; }
void CObj::Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
void CObj::Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
void CObj::Set_PosX(float _fX) { m_tInfo.fX += _fX; }
void CObj::Set_PosY(float _fY) { m_tInfo.fY += _fY; }
void CObj::Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
void CObj::Set_RenderID(RENDERID eID) { m_eRender = eID; }

RENDERID CObj::Get_RenderID() { return m_eRender; }

void CObj::Update_Rect()
{
	m_tRect.left = long(m_tInfo.fX - m_tInfo.fCX / 2.f);
	m_tRect.top = long(m_tInfo.fY - m_tInfo.fCY / 2.f);
	m_tRect.right = long(m_tInfo.fX + m_tInfo.fCX / 2.f);
	m_tRect.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2.f);

}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwFrameSpeed < GetTickCount64())
	{
		m_tFrame.iStart++;
		m_tFrame.dwTime = GetTickCount64();

		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}

}
