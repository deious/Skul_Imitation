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
	AddFontResourceEx(L"./Image/Font/PF스타더스트.ttf", FR_PRIVATE, 0);
	SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	CSoundMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Back.bmp", L"Back");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"C:\\Users\\gkstj\\OneDrive\\바탕 화면\\Project\\Skul_Imitation\\Skul_Imitation\\Image\\Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
	// UI 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player_Frame.bmp", L"pFrame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Hp_Bar.bmp", L"hBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Skul_Icon.bmp", L"sIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/SkullThrowing.bmp", L"SNormalAIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/SkullBack.bmp", L"SNormalSIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Samurai_Icon.bmp", L"SamuraiIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/SamuraiA.bmp", L"SamuraiAIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/SamuraiS.bmp", L"SamuraiSIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/ZinSamuraiA.bmp", L"ZinSamuraiAIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/ZinSamuraiS.bmp", L"ZinSamuraiSIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/ZinSamuraiSpecial.bmp", L"ZinSamuraiSpecialIcon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/BossPortrait.bmp", L"BossPortrait");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/BossHp_Bar.bmp", L"BossHp_Bar");

	// 플레이어 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Left.bmp", L"Skul_Head_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Right.bmp", L"Skul_Head_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Left.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Right.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/NoHead_Left.bmp", L"NPlayer_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/NoHead_Right.bmp", L"NPlayer_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Samurai_Left.bmp", L"Samurai_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Samurai_Right.bmp", L"Samurai_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Zin_Samurai_Left.bmp", L"ZinSamurai_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Zin_Samurai_Right.bmp", L"ZinSamurai_Right");

	// 몬스터 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Monster/Knight_Right.bmp", L"Knight_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Monster/Knight_Left.bmp", L"Knight_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Monster/Archer_Right.bmp", L"Archer_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Monster/Archer_Left.bmp", L"Archer_Left");

	// 튜토리얼 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/A_Button.bmp", L"ABtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/C_Button.bmp", L"CBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/D_Button.bmp", L"DBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/F_Button.bmp", L"FBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/I_Button.bmp", L"IBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/S_Button.bmp", L"SBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/X_Button.bmp", L"XBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/Z_Button.bmp", L"ZBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/LeftArrow_Button.bmp", L"LArrowBtn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Button/RightArrow_Button.bmp", L"RArrowBtn");
	
	// 이펙트 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Dash_Smoke_left.bmp", L"LDash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Dash_Smoke_Right.bmp", L"RDash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Double_Jump.bmp", L"Jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Player_Hit.bmp", L"Hit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Normal_Attack_Left.bmp", L"LNAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Normal_Attack_Right.bmp", L"RNAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Archer_AttackSign.bmp", L"AttackSign");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Arrow_Left.bmp", L"Arrow_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Arrow_Right.bmp", L"Arrow_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Monster_Appear.bmp", L"Monster_Appear");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Monster_Dead.bmp", L"Monster_Dead");

	// NPC 및 문 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/NPC/Stage_Door.bmp", L"StageDoor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/NPC/Dungeon_Entrance_Door.bmp", L"DungeonDoor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/NPC/Boss_Entrance_Door.bmp", L"BossDoor");
	
	
	
	// 메인게임에 이미지들을 넣어놓고 가져다 쓰자


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
	CSceneMgr::Get_Instance()->ProcessSceneChange();
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

	if (!m_hDC)
	{
		OutputDebugString(L"[문제] MainGame의 m_hDC가 nullptr입니다!\n");
	}

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
	//CSoundMgr::Destroy_Instance();
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
