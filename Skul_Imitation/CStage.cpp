#include "pch.h"
#include "CStage.h"
#include "CBmpMgr.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CPlayer.h"
#include "CCameraMgr.h"
#include "CCollisionMgr.h"

CStage::CStage()
{
}

CStage::~CStage()
{
    Release();
}

void CStage::Initialize()
{
    CCameraMgr::Get_Instance()->Set_Resolution(800, 600);
    CCameraMgr::Get_Instance()->Set_MapSize(1796, 688);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Map.bmp", L"Ground");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Edit/Tile.bmp", L"Tile");
    //CLineMgr::Get_Instance()->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());

    CTileMgr::Get_Instance()->Load_Tile();

    /*for (int i = 0; i < 3; ++i)
    {
        CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create_Obj(float(rand() % WINCX), float(rand() % WINCY)));
    }*/

}

int CStage::Update()
{
    Key_Input();
    CObjMgr::Get_Instance()->Update();
    CTileMgr::Get_Instance()->Update();
    CCameraMgr::Get_Instance()->Update();

    return 0;
}

void CStage::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    // 여기서 충돌 처리 시키면 될거 같은데?
    //CCollisionMgr::PlayerToTile();
    // CTileMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
    HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

    /*int		iScrollX = (INT)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (INT)CScrollMgr::Get_Instance()->Get_ScrollY();*/

    POINT camPos = CCameraMgr::Get_Instance()->Get_CameraPos();

    /*BitBlt(hDC,
        iScrollX,
        iScrollY,
        1920, 1280,
        hGroundDC,
        0, 0,
        SRCCOPY);*/
    BitBlt(hDC,
        0,
        0,
        1796, 688,
        hGroundDC,
        camPos.x, camPos.y,
        SRCCOPY);

    //CLineMgr::Get_Instance()->Render(hDC);


    CTileMgr::Get_Instance()->Render(hDC);
    CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
    //CTileMgr::Get_Instance()->Destroy_Instance();
}

void CStage::Key_Input()
{
    if (GetAsyncKeyState('P'))
    {
        MessageBox(g_hWnd, L"p 클릭", _T("Fail"), MB_OK);
        CTileMgr::Get_Instance()->Set_ShowTile();
    }
}
