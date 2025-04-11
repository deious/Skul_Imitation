#pragma once

#include "Define.h"

class CKeyMgr
{
private:
	CKeyMgr();
	virtual ~CKeyMgr();

public:
	bool			Key_Pressing(int _iKey);
	// 눌렀다가 뗐을 때
	bool			Key_Up(int _iKey);
	// 누른 타이밍 딱 한 번 만
	bool			Key_Down(int _iKey);
	bool			Set_ShowAll();
	bool			Get_ShowAll() const;
	void			Update();

public:
	static CKeyMgr* Get_Instance();
	static void		Destroy_Instance();

private:
	static CKeyMgr* m_pInstance;
	bool			m_bKeyState[VK_MAX];
	bool			m_bShowAll = false;
};
