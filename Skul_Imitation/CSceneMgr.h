#pragma once

#include "CTitle.h"
#include "CMenu.h"
#include "CStage.h"
#include "CEdit.h"

class CSceneMgr
{
public:
	enum SCENEID { SC_TITLE, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID				Get_SceneID();

public:
	void				Scene_Change(SCENEID eID);
	void				Update();
	void				Late_Update();
	void				Render(HDC hDC);
	void				Release();

public:
	static CSceneMgr*	Get_Instance();
	static void			Destroy_Instance();

private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;

};

// state ����(���� ����) : fsm �� ������� �ϴ� ��ü�� ���¸� ǥ���ϴ� ����, �������� ���� �� �� �ϳ��� ���¸��� ���� �� ����
// fsm (���� ���� ���) : �ڽ��� ���� �� �ִ� ������ ������ ������ �����ٴ� �ǹ�