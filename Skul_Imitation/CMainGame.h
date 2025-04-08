#pragma once

#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_hDC;

	ULONGLONG	m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];

};