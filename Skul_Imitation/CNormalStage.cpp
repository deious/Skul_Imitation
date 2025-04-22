#include "pch.h"
#include "CNormalStage.h"
#include "CObjMgr.h"
#include "CTileMgr.h"
#include "CUIMgr.h"
#include "CCollisionMgr.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"
#include "CKeyMgr.h"
#include "CGate.h"
#include "CTrigger.h"
#include "CKnightMonster.h"
#include "CArcherMonster.h"
#include "CNPC.h"

CNormalStage::CNormalStage()
{
}

CNormalStage::~CNormalStage()
{
}

void CNormalStage::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/NormalMap.bmp", L"NormalStage");
    CCameraMgr::Get_Instance()->Set_Resolution(800, 600);
    CCameraMgr::Get_Instance()->Set_MapSize(2400, 744);

    CObj* pPlayer = CSceneMgr::Get_Instance()->Get_Player();

    CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).front()->Set_Pos(200.f, WINCY >> 1);

    CTileMgr::Get_Instance()->Load_Tile(L"./Data/NormalMap.dat");
    CSoundMgr::Get_Instance()->PlayBGM(L"ChapterBgm.wav", 1.f);

    INFO tInfo = { 1100.f, 300.f, 300.f, 200.f };
    CObj* pGate = new CGate(L"DungeonDoor", tInfo, 4);
    dynamic_cast<CGate*>(pGate)->Set_Frame(0, 7, 50.f);
    
    CObjMgr::Get_Instance()->Add_Object(OBJ_TUTORIAL, pGate);

    RECT area = { 500, 300, 600, 400 };

    CObj* pTrigger = new CTrigger(area, []() {
        std::vector<Vec2> spawnPositions = {
            { 550.f, 380.f },
            { 590.f, 380.f },
            { 610.f, 380.f }
        };

        std::vector<Vec2> spawnPositions_Archer = {
            { 570.f, 380.f },
            { 600.f, 380.f },
        };

        for (const auto& pos : spawnPositions)
        {
            CObj* knight = new CKnightMonster();
            knight->Set_Pos(pos.x, pos.y);
            knight->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, knight);
        }

        for (const auto& pos : spawnPositions_Archer)
        {
            CObj* Archer = new CArcherMonster();
            Archer->Set_Pos(pos.x, pos.y);
            Archer->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, Archer);
        }
        });

    CObjMgr::Get_Instance()->Add_Object(OBJ_TRIGGER, pTrigger);

    area = { 700, 500, 800, 600 };

    pTrigger = new CTrigger(area, []() {
        std::vector<Vec2> spawnPositions = {
            { 750.f, 500.f },
            { 790.f, 500.f },
            { 810.f, 500.f }
        };

        std::vector<Vec2> spawnPositions_Archer = {
            { 770.f, 500.f },
            { 800.f, 500.f },
        };

        for (const auto& pos : spawnPositions)
        {
            CObj* knight = new CKnightMonster();
            knight->Set_Pos(pos.x, pos.y);
            knight->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, knight);
        }

        for (const auto& pos : spawnPositions_Archer)
        {
            CObj* Archer = new CArcherMonster();
            Archer->Set_Pos(pos.x, pos.y);
            Archer->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, Archer);
        }
        });

    CObjMgr::Get_Instance()->Add_Object(OBJ_TRIGGER, pTrigger);

    area = { 1400, 500, 1500, 600 };

    pTrigger = new CTrigger(area, []() {
        std::vector<Vec2> spawnPositions = {
            { 1450.f, 500.f },
            { 1480.f, 500.f },
            { 1510.f, 500.f }
        };

        std::vector<Vec2> spawnPositions_Archer = {
            { 1470.f, 500.f },
            { 1500.f, 500.f },
        };

        for (const auto& pos : spawnPositions)
        {
            CObj* knight = new CKnightMonster();
            knight->Set_Pos(pos.x, pos.y);
            knight->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, knight);
        }

        for (const auto& pos : spawnPositions_Archer)
        {
            CObj* Archer = new CArcherMonster();
            Archer->Set_Pos(pos.x, pos.y);
            Archer->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, Archer);
        }
        });

    CObjMgr::Get_Instance()->Add_Object(OBJ_TRIGGER, pTrigger);

    area = { 1600, 300, 1700, 400 };

    pTrigger = new CTrigger(area, []() {
        std::vector<Vec2> spawnPositions = {
            { 1650.f, 350.f },
            { 1680.f, 350.f },
            { 1710.f, 350.f }
        };

        std::vector<Vec2> spawnPositions_Archer = {
            { 1670.f, 350.f },
            { 1700.f, 350.f },
        };

        for (const auto& pos : spawnPositions)
        {
            CObj* knight = new CKnightMonster();
            knight->Set_Pos(pos.x, pos.y);
            knight->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, knight);
        }

        for (const auto& pos : spawnPositions_Archer)
        {
            CObj* Archer = new CArcherMonster();
            Archer->Set_Pos(pos.x, pos.y);
            Archer->Initialize();
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, Archer);
        }
        });

    CObjMgr::Get_Instance()->Add_Object(OBJ_TRIGGER, pTrigger);

    auto& monsterList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER);
    bool allDead = true;
    for (auto p : monsterList)
    {
        if (!p->Get_Dead())
        {
            allDead = false;
            break;
        }
    }

    if (allDead && !CObjMgr::Get_Instance()->Get_ObjList(OBJ_NPC).size())
    {
        INFO npcInfo = { 1325.f, 325.f, 150.f, 150.f };
        CNPC* pNpc = new CNPC;
        pNpc->Initialize();
        pNpc->Set_Pos(npcInfo.fX, npcInfo.fY);
        pNpc->Set_Activate(true);
        CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, pNpc);
    }
}

int CNormalStage::Update()
{
    Key_Input();
    CObjMgr::Get_Instance()->Update();
    CTileMgr::Get_Instance()->Update();
    CCameraMgr::Get_Instance()->Update();
    CUIMgr::Get_Instance()->Update();

    return 0;
}

void CNormalStage::Late_Update()
{
    CObjMgr::Get_Instance()->Late_Update();
    CUIMgr::Get_Instance()->Late_Update();
    CCollisionMgr::Collision_Attack();
}

void CNormalStage::Render(HDC hDC)
{
    HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"NormalStage");
    POINT camPos = CCameraMgr::Get_Instance()->Get_CameraPos();

    BitBlt(hDC,
        0,
        0,
        1726, 744,
        hGroundDC,
        camPos.x, camPos.y,
        SRCCOPY);


    CTileMgr::Get_Instance()->Render(hDC);
    CObjMgr::Get_Instance()->Render(hDC);
    CUIMgr::Get_Instance()->Render(hDC);
}

void CNormalStage::Release()
{
    CObjMgr::Get_Instance()->Release();
}

void CNormalStage::Key_Input()
{
    if (CKeyMgr::Get_Instance()->Key_Down('P'))
    {
        CKeyMgr::Get_Instance()->Set_ShowAll();
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Q'))
    {
        //MessageBox(g_hWnd, L"p Å¬¸¯", _T("Fail"), MB_OK);
        //CTileMgr::Get_Instance()->Set_ShowTile();
        //CKeyMgr::Get_Instance()->Set_ShowAll();
        //CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_BOSS);
        Release();
        CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_BOSS);
        //Release();
    }
}
