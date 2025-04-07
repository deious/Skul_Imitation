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

// state 패턴(상태 패턴) : fsm 을 기반으로 하는 객체의 상태를 표현하는 패턴, 여러개의 상태 중 단 하나의 상태만을 취할 수 있음
// fsm (유한 상태 기계) : 자신이 취할 수 있는 유한한 상태의 개수를 가진다는 의미