#include "pch.h"
#include "Define.h"
#include "CSkulZinSamurai.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAttackCollider.h"
#include "CSoundMgr.h"

CSkulZinSamurai::CSkulZinSamurai()
{
    m_fFrame[SKUL_IDLE] = { 0, 3, 0, 200, 0 };
    m_fFrame[SKUL_WALK] = { 0, 4, 1, 150, 0 };
    m_fFrame[SKUL_ATTACK] = { 0, 4, 6, 80, 0 };
    m_fFrame[SKUL_ATTACK2] = { 0, 1, 7, 80, 0 };
    m_fFrame[SKUL_ATTACK3] = { 0, 2, 8, 80, 0 };
    m_fFrame[SKUL_SKILLA] = { 0, 4, 9, 150, 0 };
    m_fFrame[SKUL_SKILLS] = { 0, 5, 10, 70, 0 };
    sSkulName = L"ZinSamurai";

    m_sSkulIcon[0] = L"ZinSamuraiAIcon";
    m_sSkulIcon[1] = L"ZinSamuraiSIcon";
    m_sSkulIcon[2] = L"ZinSamuraiSpecialIcon";

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

CSkulZinSamurai::~CSkulZinSamurai()
{
}

void CSkulZinSamurai::UseSkillA(CPlayer* pPlayer)
{
    //PlayAnimation(pPlayer, m_SkillAnim[0]);
    //MessageBox(g_hWnd, L"A스킬 발동", _T("Fail"), MB_OK);

    float x = pPlayer->Get_Info()->fX;
    float y = pPlayer->Get_Info()->fY;
    float width = 500.f;
    float height = 100.f;

    if (pPlayer->Get_Direction() == DIR_LEFT)
        x -= width * 0.5f;
    else
        x += width * 0.5f;

    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLA].iStart, m_fFrame[SKUL_SKILLA].iEnd, m_fFrame[SKUL_SKILLA].iMotion, m_fFrame[SKUL_SKILLA].dwFrameSpeed);

    auto* pCol = new CAttackCollider(
        pPlayer, x, y,
        width, height,
        0.1f, 0.2f,
        CAttackCollider::ColliderType::Static,
        ETeam::Player,
        ESkillType::SkillA,
        200
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
    CSoundMgr::Get_Instance()->Play(L"ZinSamurai_A.mp3");
}

void CSkulZinSamurai::UseSkillS(CPlayer* pPlayer)
{
    float x = pPlayer->Get_Info()->fX;
    float y = pPlayer->Get_Info()->fY;
    float width = 350.f;
    float height = 70.f;

    if (pPlayer->Get_Direction() == DIR_LEFT)
        x -= width * 0.5f;
    else
        x += width * 0.5f;

    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLS].iStart, m_fFrame[SKUL_SKILLS].iEnd, m_fFrame[SKUL_SKILLS].iMotion, m_fFrame[SKUL_SKILLS].dwFrameSpeed);

    for (int i = 0; i < 3; i++)
    {
        auto* pCol = new CAttackCollider(
            pPlayer, x, y,
            width, height,
            0.1f, 0.2f,
            CAttackCollider::ColliderType::Static,
            ETeam::Player,
            ESkillType::SkillA,
            30
        );
        pCol->Initialize();
        CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
    }
    CSoundMgr::Get_Instance()->Play(L"Double_Attack.mp3");
}

void CSkulZinSamurai::SpawnSlashCollider(CPlayer* pPlayer)
{
}

void CSkulZinSamurai::UseSkillD(CPlayer* pPlayer)
{
    pPlayer->Swap_Skul();
}

const wchar_t* CSkulZinSamurai::Get_FrameKey(CPlayer* pPlayer) const
{
    if (pPlayer->Get_Direction() == DIR_RIGHT)
    {
        return L"ZinSamurai_Right";
    }
    else
    {
        return L"ZinSamurai_Left";
    }

    return nullptr;
}

const wchar_t* CSkulZinSamurai::Get_IconKey() const
{
    return L"ZinSamuraiIcon";
}

const wstring CSkulZinSamurai::Get_SkulId() const
{
    return sSkulName;
}

FRAME* CSkulZinSamurai::Get_AllFrame()
{
    return m_fFrame;
}

