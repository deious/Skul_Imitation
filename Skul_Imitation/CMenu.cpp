#include "pch.h"
#include "CMenu.h"
#include "CObjMgr.h"
#include"CAbstractFactory.h"
#include "CButton.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"


CMenu::CMenu()
{
}

CMenu::~CMenu()
{
	Release();
}

void CMenu::Initialize()
{
	CObj* pButton = CAbstractFactory<CButton>::Create_Obj(200.f, 400.f);
	pButton->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CButton>::Create_Obj(400.f, 400.f);
	pButton->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CButton>::Create_Obj(600.f, 400.f);
	pButton->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Title/Title.bmp", L"Title");
	CSoundMgr::Get_Instance()->PlayBGM(L"TitleBgm.wav", 1.f);
}

int CMenu::Update()
{
	CObjMgr::Get_Instance()->Update();


	return 0;
}

void CMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMenu::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Title");

	BitBlt(hDC,
		0,
		0,
		WINCX, WINCY,
		hMemDC,
		0, 0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMenu::Release()
{
	//CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->StopBGM();
	CObjMgr::Get_Instance()->Delete_Object(OBJ_BUTTON);
}
