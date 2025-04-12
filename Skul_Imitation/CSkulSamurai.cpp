#include "pch.h"
#include "Define.h"
#include "CSkulSamurai.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAttackCollider.h"

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
        50
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
}

void CSkulSamurai::UseSkillS(CPlayer* pPlayer)
{
    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLS].iStart, m_fFrame[SKUL_SKILLS].iEnd, m_fFrame[SKUL_SKILLS].iMotion, m_fFrame[SKUL_SKILLS].dwFrameSpeed);
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
