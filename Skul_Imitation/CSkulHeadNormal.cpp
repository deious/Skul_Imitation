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
    if (m_bHeadThrown) return; // �̹� �������� ����

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

    // �÷��̾� �̵�
    pPlayer->Set_Pos(headPos.fX, headPos.fY);

    // �Ӹ� ����
    m_pThrownHead->Set_Dead();
    m_pThrownHead = nullptr;
    m_bHeadThrown = false;

    OutputDebugString(L"[��ųS] �Ӹ� ��ġ�� �����̵� + �� �ʱ�ȭ\n");
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
