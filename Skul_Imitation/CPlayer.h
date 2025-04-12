#pragma once
#include "CObj.h"
#include "CSkulHead.h";

//enum class MSTATE { IDLE, WALK, DASH, JUMPSTART, RISING, FALL, ATTACK, HIT, DEATH, INTERACTION, MS_END };
class CState;

//enum class EDirection { LEFT, RIGHT };

class CPlayer : public CObj
{
//public:
//	enum MSTATE { IDLE, WALK, ATTACK, HIT, DEATH, MS_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

public:
	void		ChangeState(CState* pNewState);
	void		Update_PlayerRect();
	bool		Move_Frame();
	bool		Dash_Check() const;

	void		Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed);
	void		Set_FrameKey(const TCHAR* pKey);
	void		Set_Direction(DIRECTION eDir);
	void		Set_LastDashTime();
	void		Set_UseGravity();

	int			Get_CurFrame() const;
	float		Get_Speed() const;
	float		Get_JumpPower() const;
	float		Get_Gravity() const;
	float		Get_GravityAccel() const;
	float		Get_GravityMax() const;
	bool		Get_IsJump() const;
	bool		Get_UseGravity() const;
	DIRECTION	Get_Direction() const;
	DWORD		Get_DashDuration() const;
	CSkulHead*	Get_Skul() const;

	void Set_Gravity(float f);

	void Set_Jump(bool b);

	void Create_AttackCollider(int iCombo);
	void OnHit(CAttackCollider* pCol) override;

private:
	void		Apply_Gravity();

private:
	POINT		m_tPosin;
	CState*		m_pCurState;
	DIRECTION	m_eDir = DIRECTION::DIR_RIGHT;
	CSkulHead*	m_pSkul;

	int			m_iHp;

	bool		m_bJump;
	bool		m_bUseGravity = true;
	bool		m_bShowHitText = false;

	float		m_fVelocity;
	float		m_fGravity = 0.f;
	float		m_fTime;
	float		m_fDashSpeed = 3.f;

	const float GRAVITY_ACCEL = 0.5f;		// 중력 가속도 (프레임당 증가값)
	const float GRAVITY_MAX = 10.f;			// 최대 낙하 속도 제한
	const float JUMP_POWER = -10.f;

	ULONGLONG m_dwHitTime = 0;
	ULONGLONG m_dwLastDashTime = 0;   // 마지막 대시 시각
	ULONGLONG m_dwLastHitTime = 0;
	const DWORD m_dwDashCooldown = 2000;
	const DWORD m_dwDashDuration = 300;

};
