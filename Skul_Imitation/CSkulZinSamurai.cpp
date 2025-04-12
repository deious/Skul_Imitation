#include "pch.h"
#include "Define.h"
#include "CSkulZinSamurai.h"
#include "CPlayer.h"
#include "CObjMgr.h"
#include "CAttackCollider.h"

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

void CSkulZinSamurai::UseSkillS(CPlayer* pPlayer)
{
    pPlayer->Set_Frame(m_fFrame[SKUL_SKILLS].iStart, m_fFrame[SKUL_SKILLS].iEnd, m_fFrame[SKUL_SKILLS].iMotion, m_fFrame[SKUL_SKILLS].dwFrameSpeed);
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

