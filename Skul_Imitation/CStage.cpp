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
#include "CUIPortrait.h"
#include "CUIHealthBar.h"
#include "CUIMgr.h"
#include "CUISkul.h"
#include "CKeyMgr.h"
#include "CBoss.h"

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
    /*CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player_Frame.bmp", L"pFrame");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Hp_Bar.bmp", L"hBar");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Skul_Icon.bmp", L"sIcon");*/
    //CLineMgr::Get_Instance()->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
    CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create_Obj());
    /*pButton = CAbstractFactory<CButton>::Create_Obj(600.f, 400.f);
    pButton->Set_FrameKey(L"Exit");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);*/
    /*CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIPortrait>::Create_Obj());
    CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIHealthBar>::Create_Obj());
    CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUISkul>::Create_Obj());*/

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
    CUIMgr::Get_Instance()->Update();

    return 0;
}

void CStage::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    CUIMgr::Get_Instance()->Late_Update();
    CCollisionMgr::Collision_Attack();
    // 여기서 충돌 처리 시키면 될거 같은데?
    //CCollisionMgr::PlayerToTile();
    // CTileMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
    HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
    //HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"pFrame");

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
    CUIMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
    //CTileMgr::Get_Instance()->Destroy_Instance();
}

void CStage::Key_Input()
{
    if (CKeyMgr::Get_Instance()->Key_Down('P'))
    {
        //MessageBox(g_hWnd, L"p 클릭", _T("Fail"), MB_OK);
        //CTileMgr::Get_Instance()->Set_ShowTile();
        CKeyMgr::Get_Instance()->Set_ShowAll();
    }
}
