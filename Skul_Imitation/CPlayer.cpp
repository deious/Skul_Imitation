#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CCameraMgr.h"


CPlayer::CPlayer() : m_fVelocity(0.f), m_fTime(0.f), m_bJump(false)
, m_eCurMotion(IDLE), m_ePreMotion(MS_END)
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 100.f, WINCY >> 1, 64.f, 64.f };
	m_fSpeed = 3.f;
	m_fDistance = 100.f;
	m_fVelocity = 20.f;
	m_bDead = false;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/maja2.bmp", L"Player");

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");*/
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Left.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Right.bmp", L"Player_RIGHT");

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");*/

	m_pFrameKey = L"Player_DOWN";

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 0;

	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.dwFrameSpeed = 200;

	m_eCurMotion = IDLE;
	m_eRender = RENDER_GAMEOBJECT;
	m_bStretch = false;

}

int CPlayer::Update()
{

	__super::Update_Rect();



	return NOEVENT;
}
void CPlayer::Late_Update()
{

	__super::Move_Frame();
	Key_Input();
	Offset();
	Motion_Change();
	CCameraMgr::Get_Instance()->Set_Target(m_tInfo.fX, m_tInfo.fX);
	//Jump();
}



void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (INT)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (INT)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,/// 복사 받을 dc
		m_tRect.left + iScrollX,		// 복사 받을 위치 좌표 left
		m_tRect.top + iScrollY,					// 복사 받을 위치 좌표 top
		(int)m_tInfo.fCX,				// 복사 받을 가로 사이즈
		(int)m_tInfo.fCY,				// 복사 받을 세로 사이즈
		hMemDC,							// 복사할 이미지 dc
		m_tFrame.iStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,							// 복사할 이미지의 left, top
		(int)m_tInfo.fCX,				// 복사할 이미지의 가로
		(int)m_tInfo.fCY,				// 복사할 이미지의 세로
		RGB(255, 0, 255));			// 제거할 이미지 색상 값

	/*POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

	int drawX = screenPos.x - (int)(m_tInfo.fCX / 2);
	int drawY = screenPos.y - (int)(m_tInfo.fCY / 2);

	GdiTransparentBlt(hDC,
		drawX,
		drawY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);*/
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurMotion = WALK;
		m_pFrameKey = L"Player_LEFT";
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurMotion = WALK;
		m_pFrameKey = L"Player_RIGHT";
	}

	else if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurMotion = WALK;
		m_pFrameKey = L"Player_UP";
	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurMotion = WALK;
		m_pFrameKey = L"Player_DOWN";
	}

	else if (CKeyMgr::Get_Instance()->Key_Up(VK_SPACE))
	{
		m_bJump = true;
		m_eCurMotion = WALK;
		m_pFrameKey = L"Player_UP";
	}

	else
		m_eCurMotion = IDLE;

}

//void CPlayer::Jump()
//{
//	float	fY(0.f);
//
//	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
//
//	if (m_bJump)
//	{
//		m_tInfo.fY -= (m_fVelocity * m_fTime) - (9.8f * m_fTime * m_fTime * 0.5f);
//		m_fTime += 0.2f;
//
//		if (bLineCol && (fY < m_tInfo.fY))
//		{
//			m_bJump = false;
//			m_fTime = 0.f;
//
//			m_tInfo.fY = fY;
//		}
//	}
//	else if (bLineCol)
//	{
//		m_tInfo.fY = fY;
//	}
//}

void CPlayer::Offset()
{
	int		iOffsetMinX = 100;
	int		iOffsetMaxX = 700;

	int		iOffsetMinY = 100;
	int		iOffsetMaxY = 500;

	int		iScrollX = (INT)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (INT)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (iOffsetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffsetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffsetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffsetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

}

void CPlayer::Motion_Change()
{
	if (m_ePreMotion != m_eCurMotion)
	{
		switch (m_eCurMotion)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 0;

			m_tFrame.dwTime = GetTickCount64();
			m_tFrame.dwFrameSpeed = 200;
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			m_tFrame.iMotion = 1;

			m_tFrame.dwTime = GetTickCount64();
			m_tFrame.dwFrameSpeed = 200;
			break;

		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.iMotion = 6;

			m_tFrame.dwTime = GetTickCount64();
			m_tFrame.dwFrameSpeed = 200;
			break;

		case HIT:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 3;

			m_tFrame.dwTime = GetTickCount64();
			m_tFrame.dwFrameSpeed = 200;
			break;

		case DEATH:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 4;

			m_tFrame.dwTime = GetTickCount64();
			m_tFrame.dwFrameSpeed = 200;
			break;
		}

		m_ePreMotion = m_eCurMotion;
	}

}

