#pragma once

#include "CTitle.h"
#include "CMenu.h"
#include "CStage.h"
#include "CEdit.h"
#include "CPlayer.h"

class CSceneMgr
{
public:
	enum SCENEID { SC_TITLE, SC_MENU, SC_EDIT, SC_STAGE, SC_NORMAL, SC_BOSS, SC_ENDING, SC_END };

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
	void RequestSceneChange(SCENEID eNextScene);

	void ProcessSceneChange();

private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	SCENEID				m_eCurScene;
	SCENEID				m_ePreScene;
	SCENEID				m_eNextScene;

	bool				m_bSceneChangeRequested = false;

	CObj*				m_pPlayer = nullptr;

};

// state 패턴(상태 패턴) : fsm 을 기반으로 하는 객체의 상태를 표현하는 패턴, 여러개의 상태 중 단 하나의 상태만을 취할 수 있음
// fsm (유한 상태 기계) : 자신이 취할 수 있는 유한한 상태의 개수를 가진다는 의미