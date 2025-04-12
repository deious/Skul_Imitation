#include "pch.h"
#include "CSkulHeadNormal.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CThrownHead.h"
#include "CBmpMgr.h"

CSkulHeadNormal::CSkulHeadNormal()
{
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

    CObjMgr::Get_Instance()->Add_Object(OBJ_HEAD, m_pThrownHead);
    m_bHeadThrown = true;
}

void CSkulHeadNormal::UseSkillS(CPlayer* pPlayer) 
{
    if (!m_bHeadThrown || !m_pThrownHead || !pPlayer) return;

    INFO headPos = *m_pThrownHead->Get_Info();

    // 플레이어 이동
    pPlayer->Set_Pos(headPos.fX, headPos.fY);

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
const wchar_t* CSkulHeadNormal::GetIconKey() const 
{
    return L"sIcon";
}
;
