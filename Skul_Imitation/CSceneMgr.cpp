#include "pch.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CBossStage.h"
#include "CSoundMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr)
, m_eCurScene(SC_TITLE), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

CSceneMgr::SCENEID CSceneMgr::Get_SceneID() { return m_eCurScene; }			// 오류 가능성 존재 나중에 체크해볼것

void CSceneMgr::Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_TITLE:
			m_pScene = new CTitle;
			/*if (m_pPlayer)
			{
				CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
				m_pPlayer = pPlayer;
			}*/
			break;

		case SC_MENU:
			/*if (m_pPlayer)
			{
				CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
				m_pPlayer = pPlayer;
			}*/
			m_pScene = new CMenu;
			break;

		case SC_EDIT:
			/*if (m_pPlayer)
			{
				CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
				m_pPlayer = pPlayer;
			}*/
			m_pScene = new CEdit;
			break;

		case SC_STAGE:
			/*if (m_pPlayer)
			{
				CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
				m_pPlayer = pPlayer;
			}*/
			m_pScene = new CStage;
			//m_pScene = new CBossStage;
			break;

		case SC_BOSS:
			/*if (m_pPlayer)
			{
				CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
				m_pPlayer = pPlayer;
			}*/
			m_pScene = new CBossStage;
			//m_pScene = new CStage;
			break;
		}

		CSoundMgr::Get_Instance()->StopAll();
		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

CSceneMgr* CSceneMgr::Get_Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CSceneMgr;
	}

	return m_pInstance;
}

CObj* CSceneMgr::Get_Player() const { return m_pPlayer; }

void CSceneMgr::Destroy_Instance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
