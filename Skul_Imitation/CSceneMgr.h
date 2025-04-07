#pragma once

#include "CLogo.h"
#include "CMenu.h"
#include "CStage.h"
#include "CEdit.h"

class CSceneMgr
{
public:
	enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID		Get_SceneID() { return m_eCurScene; }

public:
	void		Scene_Change(SCENEID eID);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID		 m_eCurScene;
	SCENEID		 m_ePreScene;

};

// state ����(���� ����) : fsm �� ������� �ϴ� ��ü�� ���¸� ǥ���ϴ� ����, �������� ���� �� �� �ϳ��� ���¸��� ���� �� ����
// fsm (���� ���� ���) : �ڽ��� ���� �� �ִ� ������ ������ ������ �����ٴ� �ǹ�