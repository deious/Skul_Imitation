#pragma once

#include "CTitle.h"
#include "CMenu.h"
#include "CStage.h"
#include "CEdit.h"
#include "CPlayer.h"

class CSceneMgr
{
public:
	enum SCENEID { SC_TITLE, SC_MENU, SC_EDIT, SC_STAGE, SC_BOSS, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID				Get_SceneID();
	static CSceneMgr*	Get_Instance();
	CObj*				Get_Player() const;

public:
	void				Set_Player(CObj* pPlayer);
public:
	void				Scene_Change(SCENEID eID);
	void				Update();
	void				Late_Update();
	void				Render(HDC hDC);
	void				Release();

public:
	static void			Destroy_Instance();

private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;

	CObj*				m_pPlayer = nullptr;

};

// state ����(���� ����) : fsm �� ������� �ϴ� ��ü�� ���¸� ǥ���ϴ� ����, �������� ���� �� �� �ϳ��� ���¸��� ���� �� ����
// fsm (���� ���� ���) : �ڽ��� ���� �� �ִ� ������ ������ ������ �����ٴ� �ǹ�