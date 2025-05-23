#pragma once

#include "Define.h"
#include "CHitBox.h"

class CAttackCollider;

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO*		Get_Info();
	const RECT*		Get_Rect();
	bool			Get_Dead();
	RENDERID		Get_RenderID();

	void			Set_Pos(float _fX, float _fY);
	void			Set_Direction(DIRECTION eDir);
	void			Set_Dead();
	void			Set_Angle(float _fAngle);
	void			Set_Target(CObj* pTarget);
	void			Set_PosX(float _fX);
	void			Set_PosY(float _fY);
	void			Set_FrameKey(const TCHAR* pFrameKey);
	void			Set_RenderID(RENDERID eID);
	CHitBox*		Get_HitBox() const;

public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Late_Update()PURE;	// UPDATE 연산이 끝난 이후
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;
	virtual void	Update_Rect();
	virtual void	Set_AnimFinish();

public:
	virtual void	OnHit(CAttackCollider* pCol) {};
	virtual void	OnHit(int damage);
	virtual void	OnTileCollision(float landY) {};
	virtual void	Set_Gravity(float gravity);
	virtual void	Set_Jump(bool b);
	virtual float	Get_Speed();
	virtual void	Set_Tag(wstring name);
	virtual wstring	Get_Tag();
	//bool			Move_Frame();
	bool			Is_AnimFinished() const;
	virtual const std::wstring& Get_FrameKey() const { return m_pFrameKey; }

protected:
	//void			Update_Rect();
	virtual bool			Move_Frame();

protected:
	INFO			m_tInfo;
	RECT			m_tRect;
	DIRECTION		m_eDir;
	FRAME			m_tFrame;
	RENDERID		m_eRender;

	float			m_fSpeed;
	float			m_fDistance;
	float			m_fAngle;
	bool			m_bDead = false;
	bool			m_bAnimFinished = false;

	CObj*			m_pTarget;
	CHitBox*		m_pHitBox = nullptr;
	const TCHAR*	m_pFrameKey;
	wstring			m_sTag;
};