#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	virtual ~CScrollMgr();

public:

	float					Get_ScrollX();
	float					Get_ScrollY();

	void					Set_ScrollX(float fX);
	void					Set_ScrollY(float fY);

	void					Scroll_Lock();


public:
	static CScrollMgr*		Get_Instance();

	static void				Destroy_Instance();

private:
	static CScrollMgr*		m_pInstance;

	float					m_fScrollX;
	float					m_fScrollY;

};
