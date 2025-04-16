#include "pch.h"
#include "Define.h"
#include "CSkulHeadNormal.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CThrownHead.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"

CSkulHeadNormal::CSkulHeadNormal()
{
    /*m_mapSkillFrames[ESkillType::SkillA] = { 0, 3, 9, 100 };
    m_mapSkillFrames[ESkillType::SkillS] = { 0, 1, 4, 100 };*/
    m_fFrame[SKUL_IDLE] = { 0, 3, 0, 200, 0 };
    m_fFrame[SKUL_WALK] = { 0, 7, 1, 150, 0 };
    m_fFrame[SKUL_ATTACK] = { 0, 4, 6, 100, 0 };
    m_fFrame[SKUL_ATTACK2] = { 0, 3, 7, 100, 0 };
    m_fFrame[SKUL_ATTACK3] = { 0, 3, 8, 100, 0 };
    m_fFrame[SKUL_SKILLA] = { 0, 3, 9, 50, 0 };
    m_fFrame[SKUL_SKILLS] = { 0, 1, 4, 200, 0 };
    sSkulName = L"Normal";

    m_tEffectSet.tHitEffect = {
        EFFECT_TYPE::HIT,
        L"Hit",
        Vec2(15.f, -10.f),    // vOffset
        Vec2(100.f, 100.f),     // vSize
        0, 10, 80,             // 프레임
        1.0f, 0.0f            // 스케일, 회전
    };

    m_tEffectSet.tLDashEffect = {
        EFFECT_TYPE::DASH,
        L"LDash",
        Vec2(-20.f, 0.f),
        Vec2(100.f, 100.f),
        0, 12, 100,
        1.2f, 0.0f
    };

    m_tEffectSet.tRDashEffect = {
        EFFECT_TYPE::DASH,
        L"RDash",
        Vec2(20.f, 0.f),
        Vec2(100.f, 100.f),
        0, 12, 100,
        1.2f, 0.0f
    };

    m_tEffectSet.tJumpEffect = {
        EFFECT_TYPE::JUMP,
        L"Jump",
        Vec2(0.f, 0.f),
        Vec2(150.f, 100.f),
        0, 9, 100,
        1.0f, 0.0f
    };

    m_tEffectSet.tLAttackEffect = {
        EFFECT_TYPE::ATTACK,
        L"LNAttack",
        Vec2(15.f, -10.f),    // vOffset
        Vec2(200.f, 200.f),     // vSize
        0, 9, 80,             // 프레임
        1.0f, 0.0f            // 스케일, 회전
    };

    m_tEffectSet.tRAttackEffect = {
        EFFECT_TYPE::ATTACK,
        L"RNAttack",
        Vec2(15.f, -10.f),    // vOffset
        Vec2(200.f, 200.f),     // vSize
        0, 9, 80,             // 프레임
        1.0f, 0.0f            // 스케일, 회전
    };

    m_tEffectSet.tSkillAEffect = {
        EFFECT_TYPE::SKILLA,
        L"LNAttack",
        Vec2(-20.f, 0.f),
        Vec2(200.f, 200.f),
        0, 9, 80,
        1.2f, 0.0f
    };

    m_tEffectSet.tSkillBEffect = {
        EFFECT_TYPE::SKILLB,
        L"LNAttack",
        Vec2(0.f, 0.f),
        Vec2(200.f, 200.f),
        0, 9, 80,
        1.0f, 0.0f
    };

    m_tEffectSet.tDieEffect = {
        EFFECT_TYPE::DIE,
        L"Jump",
        Vec2(0.f, 0.f),
        Vec2(150.f, 100.f),
        0, 9, 100,
        1.0f, 0.0f
    };
}

CSkulHeadNormal::~CSkulHeadNormal()
{
    if (m_pThrownHead)
    {
        m_pThrownHead->Set_Dead();
        m_pThrownHead = nullptr;
    }
}

void CSkulHeadNormal::UseSkillA(CPlayer* pPlayer) 
{
    if (m_bHeadThrown) return; // 이미 던졌으면 무시

    float x = pPlayer->Get_Info()->fX;
    float y = pPlayer->Get_Info()->fY;
    float dir = (pPlayer->Get_Direction() == DIRECTION::DIR_RIGHT) ? 1.f : -1.f;

    m_pThrownHead = new CThrownHead(pPlayer, x + dir * 10.f, y, dir);
    m_pThrownHead->Initialize();

    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLA].iStart, m_fFrame[SKUL_SKILLA].iEnd, m_fFrame[SKUL_SKILLA].iMotion, m_fFrame[SKUL_SKILLA].dwFrameSpeed);

    CObjMgr::Get_Instance()->Add_Object(OBJ_HEAD, m_pThrownHead);
    m_bHeadThrown = true;
    if (dir > 0)
        pPlayer->Set_FrameKey(L"NPlayer_Right");
    else
        pPlayer->Set_FrameKey(L"NPlayer_Left");

    CSoundMgr::Get_Instance()->Play(L"Throw_Head.wav");
}

void CSkulHeadNormal::UseSkillS(CPlayer* pPlayer) 
{
    if (!m_bHeadThrown || !m_pThrownHead || !pPlayer) return;

    INFO headPos = *m_pThrownHead->Get_Info();

    // 플레이어 이동
    pPlayer->Set_Pos(headPos.fX, headPos.fY);

    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLS].iStart, m_fFrame[SKUL_SKILLS].iEnd, m_fFrame[SKUL_SKILLS].iMotion, m_fFrame[SKUL_SKILLS].dwFrameSpeed);

    // 머리 삭제
    m_pThrownHead->Set_Dead();
    m_pThrownHead = nullptr;
    m_bHeadThrown = false;

    float dir = (pPlayer->Get_Direction() == DIRECTION::DIR_RIGHT) ? 1.f : -1.f;
    if (dir > 0)
        pPlayer->Set_FrameKey(L"Player_Right");
    else
        pPlayer->Set_FrameKey(L"Player_Left");
    OutputDebugString(L"[스킬S] 머리 위치로 순간이동 + 쿨 초기화\n");
}

void CSkulHeadNormal::Update() 
{
    if (m_bHeadThrown && (!m_pThrownHead || m_pThrownHead->Get_Dead()))
    {
        m_pThrownHead = nullptr;
        m_bHeadThrown = false;
    }
}
const wchar_t* CSkulHeadNormal::Get_IconKey() const 
{
    return L"sIcon";
}
//unordered_map<ESkillType, FrameData> CSkulHeadNormal::Get_SkillFrame() const
//{
//    return m_mapSkillFrames;
//}

void CSkulHeadNormal::UseSkillD(CPlayer* pPlayer)
{
    pPlayer->Swap_Skul();
}

const wchar_t* CSkulHeadNormal::Get_FrameKey(CPlayer* pPlayer) const
{
    if (!m_bHeadThrown)
    {
        if (pPlayer->Get_Direction() == DIR_RIGHT)
        {
            return L"Player_Right";
        }
        else
        {
            return L"Player_Left";
        }
    }
    else
    {
        if (pPlayer->Get_Direction() == DIR_RIGHT)
        {
            return L"NPlayer_Right";
        }
        else
        {
            return L"NPlayer_Left";
        }
    }

    //MessageBox(g_hWnd, L"널리턴", _T("Fail"), MB_OK);
    return nullptr;
}

FRAME* CSkulHeadNormal::Get_AllFrame()
{
    return m_fFrame;
}

const wstring CSkulHeadNormal::Get_SkulId() const
{
    return sSkulName;
}
