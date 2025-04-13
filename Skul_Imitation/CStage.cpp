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
#include "CSoundMgr.h"
#include "CSceneMgr.h"

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
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/map.bmp", L"Ground");

    CObj* pPlayer = CSceneMgr::Get_Instance()->Get_Player();

    if (!pPlayer)
    {
        // ���� ����
        pPlayer = CAbstractFactory<CPlayer>::Create_Obj();
        CSceneMgr::Get_Instance()->Set_Player(pPlayer);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
    }

    // ������ ���
    //CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);

    //CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Edit/Tile.bmp", L"Tile");
    
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player_Frame.bmp", L"pFrame");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Hp_Bar.bmp", L"hBar");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Skul_Icon.bmp", L"sIcon");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Samurai_Icon.bmp", L"SamuraiIcon");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/ZinSamurai_Icon.bmp", L"ZinSamuraiIcon");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Right.bmp", L"Skul_Head_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Left.bmp", L"Skul_Head_Left");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Left.bmp", L"Player_LEFT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Right.bmp", L"Player_RIGHT");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Samurai_Right.bmp", L"Samurai_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Samurai_Left.bmp", L"Samurai_Left");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Zin_Samurai_Right.bmp", L"ZinSamurai_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Zin_Samurai_Left.bmp", L"ZinSamurai_Left");
    //CLineMgr::Get_Instance()->Initialize();
    //CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
    CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Set_Pos(200.f, WINCY >> 1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create_Obj(0));

    CBoss* pBoss1 = dynamic_cast<CBoss*>(CAbstractFactory<CBoss>::Create_Obj(0));
    //CBoss* pBoss2 = dynamic_cast<CBoss*>(CAbstractFactory<CBoss>::Create_Obj(1));
    //pBoss1->Set_PairBoss(pBoss2);
    //pBoss2->Set_PairBoss(pBoss1);
    CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, pBoss1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, pBoss2);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create_Obj(1));
    /*pButton = CAbstractFactory<CButton>::Create_Obj(600.f, 400.f);
    pButton->Set_FrameKey(L"Exit");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);*/
    /*CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIPortrait>::Create_Obj());
    CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIHealthBar>::Create_Obj());
    CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUISkul>::Create_Obj());*/

    CTileMgr::Get_Instance()->Load_Tile(L"./Data/map.dat");
    CSoundMgr::Get_Instance()->PlayBGM(L"TutorialBgm.wav", 1.f);
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
    // ���⼭ �浹 ó�� ��Ű�� �ɰ� ������?
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
    //CTileMgr::Get_Instance()->Release();
    //CBmpMgr::Get_Instance()->Release();
    CObjMgr::Get_Instance()->Release();

    /*CSoundMgr::Destroy_Instance();
    CTileMgr::Destroy_Instance();
    CSceneMgr::Destroy_Instance();
    CBmpMgr::Destroy_Instance();
    CScrollMgr::Destroy_Instance();
    CKeyMgr::Destroy_Instance();
    CObjMgr::Destroy_Instance();
    CLineMgr::Destroy_Instance();*/

    //ReleaseDC(g_hWnd, hDC);
}

void CStage::Key_Input()
{
    if (CKeyMgr::Get_Instance()->Key_Down('P'))
    {
        //MessageBox(g_hWnd, L"p Ŭ��", _T("Fail"), MB_OK);
        //CTileMgr::Get_Instance()->Set_ShowTile();
        CKeyMgr::Get_Instance()->Set_ShowAll();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Q'))
    {
        //MessageBox(g_hWnd, L"p Ŭ��", _T("Fail"), MB_OK);
        //CTileMgr::Get_Instance()->Set_ShowTile();
        //CKeyMgr::Get_Instance()->Set_ShowAll();
        CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_BOSS);
    }
}
