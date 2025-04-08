#pragma once

#include "Define.h"

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

public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Late_Update()PURE;	// UPDATE 연산이 끝난 이후
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

protected:
	void			Update_Rect();
	void			Move_Frame();

protected:
	INFO			m_tInfo;
	RECT			m_tRect;
	DIRECTION		m_eDir;
	FRAME			m_tFrame;
	RENDERID		m_eRender;

	float			m_fSpeed;
	float			m_fDistance;
	float			m_fAngle;
	bool			m_bDead;

	CObj*			m_pTarget;
	const TCHAR*	m_pFrameKey;
};