#include "pch.h"
#include "Define.h"
#include "CSkulHeadNormal.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CThrownHead.h"
#include "CBmpMgr.h"

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
    if (pPlayer->Get_Direction() == DIR_RIGHT)
    {
        return L"Player_RIGHT";
    }
    else
    {
        return L"Player_LEFT";
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
