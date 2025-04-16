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

	m_pFrameKey = L"Player_Right";

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

int CPlayer::Get_JumpCnt() const
{
	return m_iJumpCnt;
}

int CPlayer::Get_JumpMaxCnt() const
{
	return m_iMaxJumpCnt;
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

void CPlayer::Set_JumpCntReset()
{
	m_iJumpCnt = 0;
}

void CPlayer::Set_Awaken()
{
	if (m_pSkul->Get_SkulId() == L"Samurai")
	{
		CSkulHead* pNewSkul = new CSkulZinSamurai();
		Swap_Awaken(pNewSkul);
	}
}

void CPlayer::Add_JumpCnt()
{
	if (m_iMaxJumpCnt > m_iJumpCnt)
		m_iJumpCnt++;
}

void CPlayer::Create_AttackCollider(int iCombo, int type)
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

	if (type == 0)
	{
		auto* pCol = new CAttackCollider(
			this,
			m_tInfo.fX + offsetX,
			m_tInfo.fY,
			30.f, 20.f,                     // 콜라이더 크기
			0.f, 0.1f,                      // 생성 지연 없음, 0.2초 유지
			CAttackCollider::ColliderType::Static,
			ETeam::Player,
			ESkillType::Attack,
			damage                              // 데미지
		);
		pCol->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
		//CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_COLLIDER, pCol);
	}
	else if (type == 1)
	{
		auto* pCol = new CAttackCollider(
			this,
			m_tInfo.fX + offsetX,
			m_tInfo.fY,
			30.f, 20.f,                     // 콜라이더 크기
			0.f, 0.1f,                      // 생성 지연 없음, 0.2초 유지
			CAttackCollider::ColliderType::Static,
			ETeam::Player,
			ESkillType::SkillA,
			damage                              // 데미지
		);
		pCol->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
		//CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_COLLIDER, pCol);
	}
	if (type == 2)
	{
		auto* pCol = new CAttackCollider(
			this,
			m_tInfo.fX + offsetX,
			m_tInfo.fY,
			30.f, 20.f,                     // 콜라이더 크기
			0.f, 0.1f,                      // 생성 지연 없음, 0.2초 유지
			CAttackCollider::ColliderType::Static,
			ETeam::Player,
			ESkillType::SkillS,
			damage                              // 데미지
		);
		pCol->Initialize();
		CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
		//CObjMgr::Get_Instance()->Add_Object(OBJID::OBJ_COLLIDER, pCol);
	}
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
