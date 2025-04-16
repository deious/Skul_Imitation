#include "pch.h"
#include "Define.h"
#include "CSkulSamurai.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAttackCollider.h"
#include "CSoundMgr.h"

CSkulSamurai::CSkulSamurai()
{
    /*m_mapSkillFrames[ESkillType::SkillA] = {0, 4, 9, 100};
    m_mapSkillFrames[ESkillType::SkillS] = {0, 5, 10, 80};*/
    m_fFrame[SKUL_IDLE] = { 0, 3, 0, 200, 0 };
    m_fFrame[SKUL_WALK] = { 0, 4, 1, 150, 0 };
    m_fFrame[SKUL_ATTACK] = { 0, 4, 6, 80, 0 };
    m_fFrame[SKUL_ATTACK2] = { 0, 3, 7, 80, 0 };
    m_fFrame[SKUL_ATTACK3] = { 0, 3, 8, 80, 0 };
    m_fFrame[SKUL_SKILLA] = { 0, 4, 9, 150, 0 };
    m_fFrame[SKUL_SKILLS] = { 0, 5, 10, 50, 0 };
    sSkulName = L"Samurai";

    m_sSkulIcon[0] = L"SamuraiAIcon";
    m_sSkulIcon[1] = L"SamuraiSIcon";

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

CSkulSamurai::~CSkulSamurai()
{
}

void CSkulSamurai::UseSkillA(CPlayer* pPlayer)
{
    //PlayAnimation(pPlayer, m_SkillAnim[0]);
    //MessageBox(g_hWnd, L"A스킬 발동", _T("Fail"), MB_OK);

    float x = pPlayer->Get_Info()->fX;
    float y = pPlayer->Get_Info()->fY;
    float width = 300.f;
    float height = 50.f;

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
        50
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
    CSoundMgr::Get_Instance()->Play(L"Samurai_A.mp3");
}

void CSkulSamurai::UseSkillS(CPlayer* pPlayer)
{
    //pPlayer->Set_Frame(m_fFrame[SKUL_SKILLS].iStart, m_fFrame[SKUL_SKILLS].iEnd, m_fFrame[SKUL_SKILLS].iMotion, m_fFrame[SKUL_SKILLS].dwFrameSpeed);
    float x = pPlayer->Get_Info()->fX;
    float y = pPlayer->Get_Info()->fY;
    float width = 350.f;
    float height = 70.f;

    if (pPlayer->Get_Direction() == DIR_LEFT)
        x -= width * 0.5f;
    else
        x += width * 0.5f;

    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLS].iStart, m_fFrame[SKUL_SKILLS].iEnd, m_fFrame[SKUL_SKILLS].iMotion, m_fFrame[SKUL_SKILLS].dwFrameSpeed);

    for (int i = 0; i < 2; i++)
    {
        auto* pCol = new CAttackCollider(
            pPlayer, x, y,
            width, height,
            0.1f, 0.2f,
            CAttackCollider::ColliderType::Static,
            ETeam::Player,
            ESkillType::SkillA,
            25
        );
        pCol->Initialize();
        CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
    }
    CSoundMgr::Get_Instance()->Play(L"Double_Attack.mp3");
}


void CSkulSamurai::SpawnSlashCollider(CPlayer* pPlayer)
{
}

void CSkulSamurai::UseSkillD(CPlayer* pPlayer)
{
    pPlayer->Swap_Skul();
}

const wchar_t* CSkulSamurai::Get_FrameKey(CPlayer* pPlayer) const
{
    if (pPlayer->Get_Direction() == DIR_RIGHT)
    {
        return L"Samurai_Right";
    }
    else
    {
        return L"Samurai_Left";
    }

    //MessageBox(g_hWnd, L"널리턴", _T("Fail"), MB_OK);
    return nullptr;
}

const wchar_t* CSkulSamurai::Get_IconKey() const
{
    return L"SamuraiIcon";
}

const wstring CSkulSamurai::Get_SkulId() const
{
    return sSkulName;
}

FRAME* CSkulSamurai::Get_AllFrame()
{
    return m_fFrame;
}

//unordered_map<ESkillType, FrameData> CSkulSamurai::Get_SkillFrame() const
//{
//    return unordered_map<ESkillType, FrameData>();
//}
