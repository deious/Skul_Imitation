#pragma once

#include "CLine.h"
#include "Define.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	bool				Collision_Line(float _fX, float* pY);
	void				Load_Line();

public:
	void				Initialize();
	void				Render(HDC hDC);
	void				Release();

public:
	static CLineMgr*	Get_Instance();
	static void			Destroy_Instance();

private:
	static CLineMgr*	m_pInstance;
	list<CLine*>		m_Linelist;
};

