#include "pch.h"
#include "Define.h"
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
#include "CAttackCollider.h"
#include "CSkulHeadNormal.h"
#include "CUISkul.h"
#include "CUIMgr.h"
#include "CSkulSamurai.h"
#include "CSkulZinSamurai.h"


CPlayer::CPlayer() : m_pCurState(nullptr), m_bJump(false), m_fGravity(0.f), m_fTime(0.f), m_pSkul(nullptr)
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 100.f, WINCY >> 1, 100.f, 100.f };
	m_fSpeed = 3.f;
	m_fDistance = 100.f;
	m_fVelocity = 20.f;
	m_iHp = 100;
	m_bDead = false;
	m_pSkul = new CSkulHeadNormal();
	//m_pSkul->Initialize();

	m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 30.f, 55.f);

	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Left.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Right.bmp", L"Player_RIGHT");*/

	m_pFrameKey = L"Player_RIGHT";

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 0;

	m_tFrame.dwTime = GetTickCount64();
	m_tFrame.dwFrameSpeed = 200;

	CSkulHead* pNewSkul = new CSkulSamurai();  // 새 스컬 생성
	//CSkulHead* pNewSkul = new CSkulZinSamurai();
	//pNewSkul->Initialize();

	Set_Skul(pNewSkul);							// 테스트용 등록 나중에 변경 가능

	m_eRender = RENDER_GAMEOBJECT;
	ChangeState(new CIdleState());
}

int CPlayer::Update()
{
	//m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	__super::Update_Rect();

	return NOEVENT;
}
void CPlayer::Late_Update()
{
	if (m_pCurState)
		m_pCurState->Update(this);

	Apply_Gravity();
	m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	CCollisionMgr::PlayerToTile(this, CTileMgr::Get_Instance()->Get_Tree());
	CCameraMgr::Get_Instance()->Set_Target(m_tInfo.fX, m_tInfo.fY);
}

void CPlayer::Render(HDC hDC)
{
	m_pFrameKey = this->Get_Skul()->Get_FrameKey(this);
	//if (m_eDir == DIRECTION::DIR_LEFT)
	//{
	//	//m_pFrameKey = L"Player_LEFT";
	//	m_pFrameKey = this->Get_Skul()->Get_FrameKey(this);
	//}
	//else
	//{
	//	//m_pFrameKey = L"Player_RIGHT";
	//	m_pFrameKey = this->Get_Skul()->Get_FrameKey(this);
	//}

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

	wchar_t hpText[32];
	swprintf_s(hpText, L"HP: %d", m_iHp); // 플레이어 체력

	TextOut(hDC,
		screenPos.x,
		screenPos.y - 50,
		hpText,
		(int)wcslen(hpText)
	);

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

	if (CKeyMgr::Get_Instance()->Get_ShowAll())
	{
		m_pHitBox->Render(hDC);

		POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

		RECT rc = {
			screen.x - (LONG)(m_tInfo.fCX * 0.5f),
			screen.y - (LONG)(m_tInfo.fCY * 0.5f),
			screen.x + (LONG)(m_tInfo.fCX * 0.5f),
			screen.y + (LONG)(m_tInfo.fCY * 0.5f)
		};

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
		FrameRect(hDC, &rc, hBrush);
		DeleteObject(hBrush);

		if (GetTickCount64() - m_dwHitTime < 1000)
		{
			if (m_bShowHitText)
			{
				POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY - 80);
				TextOut(hDC, screen.x, screen.y, L"플레이어 맞았음!", lstrlen(L"플레이어 히트"));
				m_bShowHitText = false;
			}
		}
	}
}

void CPlayer::Release()
{
	if (m_pCurState)
	{
		m_pCurState->Exit(this);
		delete m_pCurState;
		m_pCurState = nullptr;
	}

	Safe_Delete(m_pHitBox);
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

int CPlayer::Get_CurFrame() const
{
	return m_tFrame.iStart;
}

int CPlayer::Get_EndFrame() const
{
	return m_tFrame.iEnd;
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
DIRECTION CPlayer::Get_Direction() const { return m_eDir; }

DWORD CPlayer::Get_DashDuration() const
{
	return m_dwDashDuration;
}

CSkulHead* CPlayer::Get_Skul() const { return m_pSkul; }

void CPlayer::Set_Gravity(float f)
{
	m_fGravity = f;
}

void CPlayer::Set_Jump(bool b)
{
	m_bJump = b;
}

void CPlayer::Set_Awaken()
{
	if (m_pSkul->Get_SkulId() == L"Samurai")
	{
		CSkulHead* pNewSkul = new CSkulZinSamurai();
		Swap_Awaken(pNewSkul);
	}
}

void CPlayer::Create_AttackCollider(int iCombo)
{
	float offsetX = (m_eDir == DIRECTION::DIR_RIGHT) ? 30.f : -30.f;
	//float offsetY = -m_tInfo.fCY;
	float width = 60.f;
	float height = 40.f;
	int damage = 20;

	switch (iCombo)
	{
	case 1:
		width = 70.f;
		damage = 25;
		break;
	case 2:
		width = 80.f;
		damage = 30;
		break;
	}

	auto* pCol = new CAttackCollider(
		this,
		m_tInfo.fX + offsetX,
		m_tInfo.fY,
		30.f, 20.f,                     // 콜라이더 크기
		0.f, 0.2f,                      // 생성 지연 없음, 0.2초 유지
		CAttackCollider::ColliderType::Static,
		ETeam::Player,
		damage                              // 데미지
	);
	pCol->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_COLLIDER, pCol);
}

void CPlayer::OnHit(CAttackCollider* pCol)
{
	m_dwHitTime = GetTickCount64();
	//MessageBox(g_hWnd, L"플레이어 히트", _T("Fail"), MB_OK);
	if (GetTickCount64() - m_dwLastHitTime < 500)  // 0.5초 무적
		return;

	m_dwLastHitTime = GetTickCount64();

	m_bShowHitText = true;
	m_iHp -= pCol->Get_Damage();
	if (m_iHp <= 0)
		Set_Dead();
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

void CPlayer::Set_Direction(DIRECTION eDir)
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

void CPlayer::Set_Skul(CSkulHead* pNewSkul)
{
	if (!m_pSkul)
		m_pSkul = pNewSkul;
	else
		m_pStoredSkul = pNewSkul;
}

void CPlayer::Swap_Awaken(CSkulHead* pAwaken)
{
	if (!m_pSkul) return;  // 보조 슬롯 비어있으면 스왑 불가

	swap(m_pSkul, pAwaken);

	// UI 업데이트
	CUISkul* pUI = CUIMgr::Get_Instance()->Get_UI<CUISkul>();
	if (pUI)
		pUI->Set_FrameKey(m_pSkul->Get_IconKey());

	FRAME* tempFrame = m_pSkul->Get_AllFrame();
	m_tFrame.iStart = tempFrame[SKUL_IDLE].iStart;
	m_tFrame.iEnd = tempFrame[SKUL_IDLE].iEnd;

	//delete tempFrame;
}

void CPlayer::Swap_Skul()
{
	if (!m_pStoredSkul) return;  // 보조 슬롯 비어있으면 스왑 불가

	swap(m_pSkul, m_pStoredSkul);

	// UI 업데이트
	CUISkul* pUI = CUIMgr::Get_Instance()->Get_UI<CUISkul>();
	if (pUI)
		pUI->Set_FrameKey(m_pSkul->Get_IconKey());

	FRAME* tempFrame = m_pSkul->Get_AllFrame();
	m_tFrame.iStart = tempFrame[SKUL_IDLE].iStart;
	m_tFrame.iEnd = tempFrame[SKUL_IDLE].iEnd;

	//delete tempFrame;
}

bool CPlayer::Move_Frame()
{
	return __super::Move_Frame();
}

bool CPlayer::Dash_Check() const
{
	return GetTickCount64() - m_dwLastDashTime > m_dwDashCooldown;
}
