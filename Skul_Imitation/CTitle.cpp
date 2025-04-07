#include "pch.h"
#include "CTitle.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
	Release();
}

void CTitle::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Title/Title.bmp", L"Title");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"C:\\Users\\gkstj\\OneDrive\\바탕 화면\\Project\\Skul_Imitation\\Skul_Imitation\\Image\\Logo\\Logo.bmp", L"Back");

}

int CTitle::Update()
{
	return 0;
}

void CTitle::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
		return;
	}


}

void CTitle::Render(HDC hDC)
{
	//Rectangle(hDC, 0, 0, 200, 200);
	//if (!hDC)
	//	MessageBox(nullptr, L"hDC is null!", L"ERROR", MB_OK);
	/*HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	if (!hMemDC)
	{
		MessageBox(nullptr, L"Logo HDC가 null입니다!", L"ERROR", MB_OK);
		return;
	}

	BOOL bSuccess = BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	if (!bSuccess)
	{
		MessageBox(nullptr, L"BitBlt 실패!", L"ERROR", MB_OK);
	}*/

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Title");
	
	BitBlt(hDC,
		0,
		0,
		WINCX, WINCY,
		hMemDC,
		0, 0,
		SRCCOPY);
}

void CTitle::Release()
{
	//MCIWndClose(m_hVideo);
}
