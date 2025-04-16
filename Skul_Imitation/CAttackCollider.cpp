#include "pch.h"
#include "CAttackCollider.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"
#include <string>

CAttackCollider::CAttackCollider(CObj* pOwner, float x, float y, float width, float height,
    float delay, float duration, ColliderType type, ETeam team, ESkillType sType, int damage)
    : m_pOwner(pOwner), m_fDelay(delay), m_fDuration(duration), m_eType(type),
    m_eTeam(team), m_eSType(sType), m_iDamage(damage), m_fElapsedTime(0.f), m_bActive(false)
{
    m_tInfo.fX = x;
    m_tInfo.fY = y;
    m_tInfo.fCX = width;
    m_tInfo.fCY = height;
    __super::Update_Rect();
}

void CAttackCollider::Initialize()
{
    m_eRender = RENDER_GAMEOBJECT;
}
void CAttackCollider::Late_Update() {}

int CAttackCollider::Update()
{
    m_fElapsedTime += DELTA_TIME;

    if (!m_bActive && m_fElapsedTime >= m_fDelay)
        m_bActive = true;

    if (m_bActive && m_fElapsedTime >= m_fDelay + m_fDuration)
    {
        Set_Dead();
        return DEAD;
    }

    if (m_bActive && m_eType == ColliderType::Follow && m_pOwner)
    {
        m_tInfo.fX = m_pOwner->Get_Info()->fX;
        m_tInfo.fY = m_pOwner->Get_Info()->fY;
    }

    __super::Update_Rect();
    return 0;
}

void CAttackCollider::Render(HDC hDC)
{
    if (!m_bActive) return;

    //if (CKeyMgr::Get_Instance()->Get_ShowAll())
    //{
    //    RECT rc = *Get_Rect();
    //    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    //    FrameRect(hDC, &rc, hBrush);   // 외곽선만 그리기
    //    DeleteObject(hBrush);
    //}

    if (CKeyMgr::Get_Instance()->Get_ShowAll())
    {
        POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

        RECT drawRc;
        drawRc.left = (LONG)(screen.x - m_tInfo.fCX * 0.5f);
        drawRc.top = (LONG)(screen.y - m_tInfo.fCY * 0.5f);
        drawRc.right = (LONG)(screen.x + m_tInfo.fCX * 0.5f);
        drawRc.bottom = (LONG)(screen.y + m_tInfo.fCY * 0.5f);

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hDC, &drawRc, hBrush);
        DeleteObject(hBrush);

        std::wstring debugText = L"Y(World): " + std::to_wstring((int)m_tInfo.fY) +
            L" | Y(Screen): " + std::to_wstring(screen.y);
        TextOut(hDC, screen.x, screen.y - 20, debugText.c_str(), (int)debugText.length());
    }

    /*HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
    RECT rc = *Get_Rect();
    FillRect(hDC, &rc, hBrush);
    DeleteObject(hBrush);*/
}

void CAttackCollider::Release() {}
bool CAttackCollider::IsActive() const { return m_bActive; }
ETeam CAttackCollider::Get_Team() const { return m_eTeam; }
ESkillType CAttackCollider::Get_SkillType() const
{
    return m_eSType;
}
int CAttackCollider::Get_Damage() const { return m_iDamage; }

bool CAttackCollider::Get_Hit(CObj* pTarget) const { return m_HitTargets.count(pTarget) > 0; }

void CAttackCollider::Insert_Hit(CObj* pTarget) { m_HitTargets.insert(pTarget); }
