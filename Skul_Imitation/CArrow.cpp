#include "pch.h"
#include "CArrow.h"
#include "CAttackCollider.h"
#include "CObjMgr.h"
#include "CEffectMgr.h"
#include "CBmpMgr.h"

CArrow::CArrow(Vec2 pos, Vec2 dir, CMonster* pMonster) : CProjectile(pos, dir)
{
    //m_Dir = dir;
    m_tInfo.fCX = 25.f;
    m_tInfo.fCY = 6.f;
    /*m_tInfo.fX = pMonster->Get_Info()->fX;
    m_tInfo.fY = pMonster->Get_Info()->fY;*/
    m_fSpeed = 30.f;
    //m_Dir = dir;
    /*wchar_t szBuf[128];
    swprintf_s(szBuf, L"[ARROW DIR] m_Dir.x = %.2f, m_Dir.y = %.2f\n", m_Dir.x, m_Dir.y);
    OutputDebugString(szBuf);*/

    wchar_t szBuf2[128];
    swprintf_s(szBuf2, L"[화살 생성 위치 : ] m_tInfo.x = %.2f, m_tInfo.y = %.2f\n", m_tInfo.fX, m_tInfo.fY);
    OutputDebugString(szBuf2);

    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    float direction = (pPlayer->Get_Info()->fX > pMonster->Get_Info()->fX) ? 1.f : -1.f;

    EffectInfo effect;
    if (direction > 0)
    {
        m_pFrameKey = L"Arrow_Right";
        effect.vOffset = { 250.f, 0.f };
    }
    else
    {
        m_pFrameKey = L"Arrow_Left";
        effect.vOffset = { -250.f, 0.f };
    }

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 0;

    effect.eType = EFFECT_TYPE::SKILLA;
    effect.sFramekey = L"AttackSign";
    //effect.vOffset = {200.f, -25.f};
    effect.vSize = Vec2(500.f, 50.f); // 이펙트 크기
    effect.iStartFrame = 0;
    effect.iEndFrame = 18;
    effect.iFrameSpeed = 50;
    effect.fScale = 1.f;
    effect.fRotation = 0.f;
    effect.rId = RENDER_PRIORITY;
    CEffectMgr::Get_Instance()->Add_Effect(effect, pos);

    CAttackCollider* pCol = new CAttackCollider(
        this,
        m_tInfo.fX, m_tInfo.fY,
        25.f, 6.f,     // width, height
        0.f, 2.f,       // delay, duration
        CAttackCollider::ColliderType::Follow,
        ETeam::Enemy,
        ESkillType::Attack,
        25
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
}

int CArrow::Update()
{
    if (m_bDead)
        return DEAD;

    /*m_tInfo.fX += m_Dir.x * m_fSpeed * DELTA_TIME;
    m_tInfo.fY += m_Dir.y * m_fSpeed * DELTA_TIME;*/
    /*wchar_t szBuf[128];
    swprintf_s(szBuf, L"[ARROW DIR] m_Dir.x = %.2f, m_Dir.y = %.2f\n", m_Dir.x, m_Dir.y);
    OutputDebugString(szBuf);

    wchar_t szBuf2[128];
    swprintf_s(szBuf2, L"[m_tInfo] m_tInfo.x = %.2f, m_tInfo.y = %.2f\n", m_tInfo.fX, m_tInfo.fY);
    OutputDebugString(szBuf2);*/

    /*if (m_tInfo.fX < 0 || m_tInfo.fX > 4000.f || m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
        return DEAD;*/

    __super::Update();

    return 0;
}

void CArrow::Render(HDC hDC)
{
    if (m_bDead) return;

    /*if (m_tInfo.fX < 0 || m_tInfo.fX > WINCX || m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
        return;*/

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    if (!hMemDC) return;

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);
    //POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_Pos.x, (int)m_Pos.y);

    GdiTransparentBlt(
        hDC,
        screen.x - (int)(m_tInfo.fCX * 0.5f),
        screen.y - (int)(m_tInfo.fCY * 0.5f),
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        0, 0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)
    );

    /*m_tFrame.iStart* (int)m_tInfo.fCX,
        m_tFrame.iMotion* (int)m_tInfo.fCY

        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,*/
}

void CArrow::OnHit(CAttackCollider* pCol)
{
    m_bDead = true;
}


void CArrow::Set_Frame(int iStart, int iEnd, DWORD dwSpeed)
{
    m_tFrame.iStart = iStart;
    m_tFrame.iEnd = iEnd;
    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = dwSpeed;
}

void CArrow::Set_Active(bool bActive) { m_bActive = bActive; }

bool CArrow::Is_Active() const { return m_bActive; }