#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CCameraMgr.h"
#include "CCollisionMgr.h"
#include "CTileMgr.h"
#include "CIdleState.h"


CPlayer::CPlayer() : m_pCurState(nullptr), m_bJump(false), m_fGravity(0.f), m_fTime(0.f)
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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Left.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Right.bmp", L"Player_RIGHT");

	m_pFrameKey = L"Player_RIGHT";

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 0;

	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.dwFrameSpeed = 200;

	//m_eCurMotion = MSTATE::IDLE;
	m_eRender = RENDER_GAMEOBJECT;
	ChangeState(new CIdleState());
	//m_bStretch = false;
}

int CPlayer::Update()
{
	__super::Update_Rect();

	return NOEVENT;
}
void CPlayer::Late_Update()
{
	if (m_pCurState)
		m_pCurState->Update(this);

	Apply_Gravity();
	CCollisionMgr::PlayerToTile(this, CTileMgr::Get_Instance()->Get_Tree());
	CCameraMgr::Get_Instance()->Set_Target(m_tInfo.fX, m_tInfo.fY);
}

void CPlayer::Render(HDC hDC)
{
	if (m_eDir == EDirection::LEFT)
		m_pFrameKey = L"Player_LEFT";
	else
		m_pFrameKey = L"Player_RIGHT";

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

	int drawX = screenPos.x - (int)(m_tInfo.fCX * 0.5f);
	int drawY = screenPos.y - (int)(m_tInfo.fCY * 0.5f);

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
	);
}

void CPlayer::Release()
{
	if (m_pCurState)
	{
		m_pCurState->Exit(this);
		delete m_pCurState;
		m_pCurState = nullptr;
	}
}

void CPlayer::ChangeState(CState* pNewState)
{
	if (m_pCurState)
	{
		m_pCurState->Exit(this);
		delete m_pCurState;
	}
	m_pCurState = pNewState;
	m_pCurState->Enter(this);
}

void CPlayer::Update_PlayerRect()
{
	Update_Rect();
}

float CPlayer::Get_Speed() const { return m_fSpeed; }
float CPlayer::Get_JumpPower() const
{
	return JUMP_POWER;
}
float CPlayer::Get_Gravity() const
{
	return m_fGravity;
}
float CPlayer::Get_GravityAccel() const
{
	return GRAVITY_ACCEL;
}
float CPlayer::Get_GravityMax() const
{
	return GRAVITY_MAX;
}
bool CPlayer::Get_IsJump() const
{
	return m_bJump;
}
bool CPlayer::Get_UseGravity() const
{
	return m_bUseGravity;
}
EDirection CPlayer::Get_Direction() const { return m_eDir; }

DWORD CPlayer::Get_DashDuration() const
{
	return m_dwDashDuration;
}

void CPlayer::Set_Gravity(float f)
{
	m_fGravity = f;
}

void CPlayer::Set_Jump(bool b)
{
	m_bJump = b;
}

//void CPlayer::Key_Input()
//{
//	if (CKeyMgr::Get_Instance()->Key_Down('X') && !m_bJump)
//	{
//		if (!m_bAttack)
//		{
//			m_bAttack = true;
//			m_iComboCount = 0;
//			m_dwLastAttackTime = GetTickCount64();
//			m_eCurMotion = MSTATE::ATTACK;
//			m_bForceMotionChange = true;
//		}
//		else if (!m_bAttackInputQueued && m_iComboCount < 2)
//		{
//			m_bAttackInputQueued = true;
//			m_dwLastAttackTime = GetTickCount64();
//		}
//		return;
//	}
//
//	if (m_bAttack)
//	{
//		// 공격 외 키가 눌리면 공격 중단
//		if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) ||
//			GetAsyncKeyState('C') || GetAsyncKeyState('Z') || GetAsyncKeyState('F'))
//		{
//			m_bAttack = false;
//			m_iComboCount = 0;
//			m_eCurMotion = MSTATE::IDLE;  // 또는 WALK, JUMP 등으로 바꾸기
//			m_bForceMotionChange = true;
//		}
//
//		return;
//	}
//
//	// 공중일 때는 이동만 허용
//	if (m_bJump)
//	{
//		if (GetAsyncKeyState(VK_LEFT))
//		{
//			m_tInfo.fX -= m_fSpeed;
//			m_pFrameKey = L"Player_LEFT";
//		}
//		else if (GetAsyncKeyState(VK_RIGHT))
//		{
//			m_tInfo.fX += m_fSpeed;
//			m_pFrameKey = L"Player_RIGHT";
//		}
//		return;
//	}
//
//	if (GetAsyncKeyState(VK_LEFT))
//	{
//		m_tInfo.fX -= m_fSpeed;
//		m_eCurMotion = MSTATE::WALK;
//		m_pFrameKey = L"Player_LEFT";
//	}
//	else if (GetAsyncKeyState(VK_RIGHT))
//	{
//		m_tInfo.fX += m_fSpeed;
//		m_eCurMotion = MSTATE::WALK;
//		m_pFrameKey = L"Player_RIGHT";
//	}
//	else if (GetAsyncKeyState('Z'))					// 대쉬 -> 쿨 타임 필요
//	{
//		if (m_pFrameKey == L"Player_LEFT")
//		{
//			m_tInfo.fX += -m_fSpeed * 3.f;
//		}
//		else
//		{
//			m_tInfo.fX += m_fSpeed * 3.f;
//		}
//
//		m_eCurMotion = MSTATE::DASH;
//		//m_pFrameKey = L"Player_DASH";
//	}
//	else if (GetAsyncKeyState('F'))					// 상호작용
//	{
//		m_tInfo.fY += m_fSpeed;
//		m_eCurMotion = MSTATE::INTERACTION;
//		//m_pFrameKey = L"Player_INTERACTION";
//	}
//	else if (!m_bAttack && !m_bJump && m_eCurMotion != MSTATE::IDLE)
//	{
//		m_eCurMotion = MSTATE::IDLE;
//		m_bForceMotionChange = true;
//	}
//	/*else 
//	{
//		m_eCurMotion = MSTATE::IDLE;
//		m_bForceMotionChange = true;
//	}*/
//
//}


//void CPlayer::Apply_Gravity()
//{
//	//float fLandY = 0.f;
//	//bool bOnGround = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fLandY);
//
//	//if (!bOnGround || m_tInfo.fY < fLandY)
//	//{
//	//	//m_bJump = true;
//
//	//	// 중력 증가
//	//	m_fGravity += GRAVITY_ACCEL;
//	//	if (m_fGravity > GRAVITY_MAX)
//	//		m_fGravity = GRAVITY_MAX;
//
//	//	m_tInfo.fY += m_fGravity;
//
//	//	if (m_fGravity < 0.f && m_eCurMotion != MSTATE::RISING && m_eCurMotion != MSTATE::JUMPSTART)
//	//	{
//	//		m_eCurMotion = MSTATE::RISING;
//	//		m_bForceMotionChange = true;
//	//	}
//	//	else if (m_fGravity > 0.f && m_eCurMotion != MSTATE::FALL)
//	//	{
//	//		m_eCurMotion = MSTATE::FALL;
//	//		m_bForceMotionChange = true;
//	//	}
//	//}
//	//else
//	//{
//	//	if (m_bJump || m_eCurMotion == MSTATE::FALL || m_eCurMotion == MSTATE::RISING)
//	//	{
//	//		m_bJump = false;
//	//		m_fGravity = 0.f;
//	//		m_tInfo.fY = fLandY;
//
//	//		m_eCurMotion = MSTATE::IDLE;
//	//		m_bForceMotionChange = true;
//	//	}
//	//}
//	float fLandY = 0.f;
//	bool bOnGround = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fLandY);
//
//	if (!bOnGround || m_tInfo.fY < fLandY)
//	{
//		m_fGravity += GRAVITY_ACCEL;
//		if (m_fGravity > GRAVITY_MAX)
//			m_fGravity = GRAVITY_MAX;
//
//		m_tInfo.fY += m_fGravity;
//
//		// 공격 중이면 점프 상태로 전이하지 않음
//		if (!m_bAttack)
//		{
//			if (m_fGravity < 0.f && m_eCurMotion != MSTATE::RISING && m_eCurMotion != MSTATE::JUMPSTART)
//			{
//				m_eCurMotion = MSTATE::RISING;
//				m_bForceMotionChange = true;
//			}
//			else if (m_fGravity > 0.f && m_eCurMotion != MSTATE::FALL)
//			{
//				m_eCurMotion = MSTATE::FALL;
//				m_bForceMotionChange = true;
//			}
//		}
//	}
//	else
//	{
//		if (m_bJump || m_eCurMotion == MSTATE::FALL || m_eCurMotion == MSTATE::RISING)
//		{
//			m_bJump = false;
//			m_fGravity = 0.f;
//			m_tInfo.fY = fLandY;
//
//			//if (!m_bAttack) // 공격 중이면 IDLE로 바꾸지 말 것
//			//{
//			//	m_eCurMotion = MSTATE::IDLE;
//			//	m_bForceMotionChange = true;
//			//}
//			if (m_bAttack)
//			{
//				m_bAttack = false; // 점프 끝나면 공격도 초기화
//				m_bAttackInputQueued = false;
//				m_iComboCount = 0;
//			}
//
//			m_eCurMotion = MSTATE::IDLE;
//			m_bForceMotionChange = true;
//		}
//	}
//}

void CPlayer::Apply_Gravity()
{
	if (!m_bUseGravity)
	{
		return;
	}

	float fLandY = 0.f;
	bool bOnGround = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fLandY);

	if (!bOnGround || m_tInfo.fY < fLandY)
	{
		m_fGravity += GRAVITY_ACCEL;
		if (m_fGravity > GRAVITY_MAX)
			m_fGravity = GRAVITY_MAX;

		m_tInfo.fY += m_fGravity;
	}
	else
	{
		if (m_bJump)
		{
			m_bJump = false;
			m_fGravity = 0.f;
			m_tInfo.fY = fLandY;
		}
	}
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

//void CPlayer::Attack(bool bAnimEnd)
//{
//	//if (m_bJump) return;
//
//	if (GetTickCount64() - m_dwLastAttackTime > COMBO_MAX_DELAY)
//	{
//		m_bAttack = false;
//		m_bAttackInputQueued = false;
//		m_iComboCount = 0;
//		m_eCurMotion = MSTATE::IDLE;
//		m_bForceMotionChange = true;
//		return;
//	}
//
//	if (bAnimEnd)
//	{
//		if (m_bAttackInputQueued && m_iComboCount < 2)
//		{
//			++m_iComboCount;
//			m_bAttackInputQueued = false;
//			m_dwLastAttackTime = GetTickCount64();
//			m_eCurMotion = MSTATE::ATTACK;
//			m_bForceMotionChange = true;
//		}
//		else
//		{
//			m_bAttack = false;
//			m_iComboCount = 0;
//			m_eCurMotion = MSTATE::IDLE;
//			m_bForceMotionChange = true;
//		}
//	}
//}

//void CPlayer::Attack()
//{
//	// 콤보 유지시간 초과 시 리셋
//	if (m_bAttack && GetTickCount64() - m_dwLastAttackTime > COMBO_MAX_DELAY)
//	{
//		m_bAttackInputQueued = false;
//		m_bAttack = false;
//		m_iComboCount = 0;
//		m_eCurMotion = MSTATE::IDLE;
//		m_bForceMotionChange = true;
//		return;
//	}
//
//	bool bAnimEnd = __super::Move_Frame(); // 여기서 애니메이션 상태 확인도 포함
//
//	if (!m_bAttack)
//	{
//		m_bAttack = true;
//		m_iComboCount = 0;
//		m_dwLastAttackTime = GetTickCount64();
//		m_eCurMotion = MSTATE::ATTACK;
//		m_bForceMotionChange = true;
//	}
//	else
//	{
//		if (bAnimEnd)
//		{
//			if (m_bAttackInputQueued && m_iComboCount < 2)
//			{
//				++m_iComboCount;
//				m_bAttackInputQueued = false;
//				m_dwLastAttackTime = GetTickCount64();
//				m_eCurMotion = MSTATE::ATTACK;
//				m_bForceMotionChange = true;
//			}
//			else
//			{
//				m_bAttack = false;
//				m_iComboCount = 0;
//				m_eCurMotion = MSTATE::IDLE;
//				m_bForceMotionChange = true;
//			}
//		}
//	}
//}

//void CPlayer::Jump()
//{
//	m_tInfo.fY -= m_fSpeed;
//}

//void CPlayer::Motion_Change()
//{
//	if (m_ePreMotion != m_eCurMotion || m_bForceMotionChange)
//	{
//		m_tFrame.iStart = 0;
//		switch (m_eCurMotion)
//		{
//		case MSTATE::IDLE:
//			m_tFrame.iEnd = 3;
//			m_tFrame.iMotion = 0;
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::WALK:
//			m_tFrame.iEnd = 7;
//			m_tFrame.iMotion = 1;
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::ATTACK:
//			switch (m_iComboCount)
//			{
//			case 0: // 1타
//				m_tFrame.iEnd = 4;
//				m_tFrame.iMotion = 6;
//				break;
//			case 1: // 2타
//				m_tFrame.iEnd = 3;
//				m_tFrame.iMotion = 7;
//				break;
//			case 2: // 3타
//				m_tFrame.iEnd = 3;
//				m_tFrame.iMotion = 8;
//				break;
//			}
//			m_tFrame.dwFrameSpeed = 100;
//			break;
//		case MSTATE::DASH:
//			m_tFrame.iEnd = 0;
//			m_tFrame.iMotion = 2;
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::JUMPSTART:
//			m_tFrame.iEnd = 1;
//			m_tFrame.iMotion = 4;
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::RISING:
//			m_tFrame.iEnd = 1;
//			m_tFrame.iMotion = 5;
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::FALL:
//			m_tFrame.iEnd = 2;
//			m_tFrame.iMotion = 6;
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::HIT:
//			m_tFrame.iEnd = 1;
//			m_tFrame.iMotion = 3;
//
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//
//		case MSTATE::DEATH:
//			m_tFrame.iEnd = 3;
//			m_tFrame.iMotion = 4;
//
//			m_tFrame.dwFrameSpeed = 200;
//			break;
//		}
//
//		m_tFrame.dwTime = GetTickCount64();
//		m_ePreMotion = m_eCurMotion;
//		m_bForceMotionChange = false;
//	}
//
//}

void CPlayer::Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed)
{
	m_tFrame.iStart = iStart;
	m_tFrame.iEnd = iEnd;
	m_tFrame.iMotion = iMotion;
	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.dwFrameSpeed = dwSpeed;
}

void CPlayer::Set_FrameKey(const TCHAR* pKey)
{
	m_pFrameKey = pKey;
}

void CPlayer::Set_Direction(EDirection eDir)
{
	m_eDir = eDir;
}

void CPlayer::Set_LastDashTime()
{
	m_dwLastDashTime = GetTickCount64();
}

void CPlayer::Set_UseGravity()
{
	m_bUseGravity = !m_bUseGravity;
}

bool CPlayer::Move_Frame()
{
	return __super::Move_Frame();
}

bool CPlayer::Dash_Check() const
{
	return GetTickCount64() - m_dwLastDashTime > m_dwDashCooldown;
}
