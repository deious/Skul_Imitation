#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CCollisionMgr.h"
#include "CMouse.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"
#include "CUIMgr.h"
#include "CUIPortrait.h"
#include "CUIHealthBar.h"
#include "CUISkul.h"
#include "CSoundMgr.h"

CMainGame::CMainGame() :m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	/*m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBackBmp = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBackBmp);*/
	CSoundMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Back.bmp", L"Back");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"C:\\Users\\gkstj\\OneDrive\\바탕 화면\\Project\\Skul_Imitation\\Skul_Imitation\\Image\\Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player_Frame.bmp", L"pFrame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Hp_Bar.bmp", L"hBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Skul_Icon.bmp", L"sIcon");

	CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIPortrait>::Create_Obj());
	CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIHealthBar>::Create_Obj());
	CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUISkul>::Create_Obj());

	m_hMemDC = CreateCompatibleDC(m_hDC);
	m_hBackBmp = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBackBmp);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CMainGame::Render()
{
	m_iFPS++;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

	/*if (CSceneMgr::SC_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;*/


	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC,
		0,
		0,
		WINCX, WINCY,
		hBackDC,
		0, 0,
		SRCCOPY);

	//Rectangle(m_hMemDC, 0, 0, WINCX, WINCY);

	// 현재 씬 렌더
	//CSceneMgr::Get_Instance()->Render(m_hMemDC); // ← 이때 Stage::Render() 호출됨

	// 백버퍼 → 화면 출력
	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	CSoundMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	/*SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBackBmp);
	DeleteDC(m_hMemDC);*/
}
