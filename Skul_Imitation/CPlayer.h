#pragma once
#include "CObj.h"
class CPlayer : public CObj
{
public:
	enum MSTATE { IDLE, WALK, ATTACK, HIT, DEATH, MS_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

private:
	void		Key_Input();
	void		Jump();

	void		Offset();
	void		Motion_Change();

private:
	POINT		m_tPosin;

	bool		m_bJump;
	float		m_fVelocity;
	float		m_fTime;

	MSTATE		m_eCurMotion;
	MSTATE		m_ePreMotion;

	bool		m_bStretch;

};
