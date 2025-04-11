#pragma once

#include "Define.h"

class CKeyMgr
{
private:
	CKeyMgr();
	virtual ~CKeyMgr();

public:
	bool			Key_Pressing(int _iKey);
	// �����ٰ� ���� ��
	bool			Key_Up(int _iKey);
	// ���� Ÿ�̹� �� �� �� ��
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
