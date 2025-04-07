#include "pch.h"
#include "CStage.h"
#include "CBmpMgr.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"

CStage::CStage()
{
}

CStage::~CStage()
{
    Release();
}

void CStage::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
    //CLineMgr::Get_Instance()->Initialize();
    //CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());

    //CTileMgr::Get_Instance()->Load_Tile();

    /*for (int i = 0; i < 3; ++i)
    {
        CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create_Obj(float(rand() % WINCX), float(rand() % WINCY)));
    }*/

}

int CStage::Update()
{
    CObjMgr::Get_Instance()->Update();
    CTileMgr::Get_Instance()->Update();

    return 0;
}

void CStage::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    // CTileMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
    HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

    int		iScrollX = (INT)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (INT)CScrollMgr::Get_Instance()->Get_ScrollY();

    BitBlt(hDC,
        iScrollX,
        iScrollY,
        1920, 1280,
        hGroundDC,
        0, 0,
        SRCCOPY);

    //CLineMgr::Get_Instance()->Render(hDC);


    //CTileMgr::Get_Instance()->Render(hDC);

    CObjMgr::Get_Instance()->Render(hDC);


}

void CStage::Release()
{
    //CTileMgr::Get_Instance()->Destroy_Instance();
}
