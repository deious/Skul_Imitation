#include "pch.h"
#include "CBossStage.h"
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
#include "CBossController.h"

//bool g_bIsTeamPatternTime = false;
//float g_fTeamPatternTimer = 0.f;
//int g_iTeamPatternIndex = 0;
//int g_iWaitingBossID = -1;
//bool g_bTeamPatternStarted = false;

CBossStage::CBossStage()
{
}

CBossStage::~CBossStage()
{
    Release();
}

void CBossStage::Initialize()
{
    CCameraMgr::Get_Instance()->Set_Resolution(800, 600);
    CCameraMgr::Get_Instance()->Set_MapSize(800, 600);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BossMap.bmp", L"BossGround");

    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player_Frame.bmp", L"pFrame");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Hp_Bar.bmp", L"hBar");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Skul_Icon.bmp", L"sIcon");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Samurai_Icon.bmp", L"SamuraiIcon");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/ZinSamurai_Icon.bmp", L"ZinSamuraiIcon");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Right.bmp", L"Skul_Head_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Left.bmp", L"Skul_Head_Left");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Left.bmp", L"Player_Left");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Skul_Right.bmp", L"Player_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Samurai_Right.bmp", L"Samurai_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Samurai_Left.bmp", L"Samurai_Left");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Zin_Samurai_Right.bmp", L"ZinSamurai_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Zin_Samurai_Left.bmp", L"ZinSamurai_Left");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/tempLightning.bmp", L"temp2");

    //CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Edit/BossTile.bmp", L"Tile");
    /*CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player_Frame.bmp", L"pFrame");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Hp_Bar.bmp", L"hBar");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Skul_Icon.bmp", L"sIcon");*/
    //CLineMgr::Get_Instance()->Initialize();

    CObj* pPlayer = CSceneMgr::Get_Instance()->Get_Player();

    if (!pPlayer)
    {
        MessageBox(g_hWnd, L"플레이어 없음", _T("Fail"), MB_OK);
        pPlayer = CAbstractFactory<CPlayer>::Create_Obj();
        CSceneMgr::Get_Instance()->Set_Player(pPlayer);
        CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);
    }

    /*CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pPlayer);*/

    //CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj());
    CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Set_Pos(200.f, WINCY >> 1);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create_Obj(0));

    CBoss* pBoss1 = dynamic_cast<CBoss*>(CAbstractFactory<CBoss>::Create_Obj(0));
    CBoss* pBoss2 = dynamic_cast<CBoss*>(CAbstractFactory<CBoss>::Create_Obj(1));
    pBoss1->Set_PairBoss(pBoss2);
    pBoss2->Set_PairBoss(pBoss1);

    pController = new CBossController();
    pController->Initialize(pBoss1, pBoss2);
    pBoss1->Set_Controller(pController);
    pBoss2->Set_Controller(pController);

    CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, pBoss1);
    CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, pBoss2);
    //CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss>::Create_Obj(1));
    /*pButton = CAbstractFactory<CButton>::Create_Obj(600.f, 400.f);
    pButton->Set_FrameKey(L"Exit");
    CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);*/
    /*CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIPortrait>::Create_Obj());
    CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUIHealthBar>::Create_Obj());
    CUIMgr::Get_Instance()->Add_UI(CAbstractFactory<CUISkul>::Create_Obj());*/

    CTileMgr::Get_Instance()->Load_Tile(L"./Data/BossMap.dat");
    CSoundMgr::Get_Instance()->PlayBGM(L"BossBgm.wav", 1.f);
    /*for (int i = 0; i < 3; ++i)
    {
        CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create_Obj(float(rand() % WINCX), float(rand() % WINCY)));
    }*/
    //CCameraMgr::Get_Instance()->Set_Target(pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY);
}

int CBossStage::Update()
{
    Key_Input();
    CObjMgr::Get_Instance()->Update();
    CTileMgr::Get_Instance()->Update();
    CCameraMgr::Get_Instance()->Update();
    CUIMgr::Get_Instance()->Update();
    pController->Update();

    return 0;
}

void CBossStage::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    CUIMgr::Get_Instance()->Late_Update();
    CCollisionMgr::Collision_Attack();
    // 여기서 충돌 처리 시키면 될거 같은데?
    //CCollisionMgr::PlayerToTile();
    // CTileMgr::Get_Instance()->Late_Update();
}

void CBossStage::Render(HDC hDC)
{
    OutputDebugString(L"[CBossStage::Render] 호출됨\n");
    HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BossGround");
    if (!hGroundDC)
    {
        OutputDebugString(L"[오류] Ground 이미지를 찾을 수 없습니다!\n");
    }
    else
    {
        OutputDebugString(L"[성공] Ground 이미지 로드됨\n");
    }
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
    if (!BitBlt(hDC,
        0,
        0,
        800, 600,
        hGroundDC,
        camPos.x, camPos.y,
        SRCCOPY))
    {
        OutputDebugString(L"[BitBlt 실패!] 화면 출력 실패\n");
    }

    //CLineMgr::Get_Instance()->Render(hDC);


    CTileMgr::Get_Instance()->Render(hDC);
    CObjMgr::Get_Instance()->Render(hDC);
    CUIMgr::Get_Instance()->Render(hDC);
}

void CBossStage::Release()
{
    CObjMgr::Get_Instance()->Release();
    //CTileMgr::Get_Instance()->Destroy_Instance();
}

void CBossStage::Key_Input()
{
    if (CKeyMgr::Get_Instance()->Key_Down('P'))
    {
        //MessageBox(g_hWnd, L"p 클릭", _T("Fail"), MB_OK);
        //CTileMgr::Get_Instance()->Set_ShowTile();
        CKeyMgr::Get_Instance()->Set_ShowAll();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Q'))
    {
        //MessageBox(g_hWnd, L"p 클릭", _T("Fail"), MB_OK);
        //CTileMgr::Get_Instance()->Set_ShowTile();
        //CKeyMgr::Get_Instance()->Set_ShowAll();
        CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_STAGE);
    }
}
