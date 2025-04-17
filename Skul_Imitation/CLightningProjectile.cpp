#include "pch.h"
#include "CLightningProjectile.h"
#include "CAttackCollider.h"
#include "CObjMgr.h"
#include "CEffectMgr.h"

CLightningProjectile::CLightningProjectile(Vec2 pos, Vec2 dir, int bossId)
    : CProjectile(pos, dir)
{
    m_tInfo.fCX = 60.f;
    m_tInfo.fCY = 20.f;
    m_fSpeed = 100.f;
    m_iBossId = bossId;

    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    CObj* pBoss = CObjMgr::Get_Instance()->Get_Boss(m_iBossId);
    float direction = (pPlayer->Get_Info()->fX > pBoss->Get_Info()->fX) ? 1.f : -1.f;

    if (direction > 0)
    {
        m_pFrameKey = L"Projectile_Right";
        m_sEffectKey = L"Lightning_Right";
    }
    else
    {
        m_pFrameKey = L"Projectile_Left";
        m_sEffectKey = L"Lightning_Left";
    }

    EffectInfo effect;
    effect.eType = EFFECT_TYPE::SKILLA;
    effect.sFramekey = m_sEffectKey.c_str();
    effect.vOffset;
    effect.vSize = Vec2(96.f, 31.f); // ÀÌÆåÆ® Å©±â
    effect.iStartFrame = 0;
    effect.iEndFrame = 19;
    effect.iFrameSpeed = 50;
    effect.fScale = 1.f;
    effect.fRotation = 0.f;

    CEffectMgr::Get_Instance()->Add_Effect(effect, pos);
 
    CAttackCollider* pCol = new CAttackCollider(
        this,
        m_tInfo.fX, m_tInfo.fY,
        60.f, 20.f,     // width, height
        0.f, 2.f,       // delay, duration
        CAttackCollider::ColliderType::Follow,
        ETeam::Enemy,
        ESkillType::Attack,
        20
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);
    Set_Frame(0, 19, 0, 150);
}

int CLightningProjectile::Update()
{
    if (m_bDead)
        return DEAD;

    m_tInfo.fX += m_Dir.x * m_fSpeed * DELTA_TIME;
    m_tInfo.fY += m_Dir.y * m_fSpeed * DELTA_TIME;

    if (m_tInfo.fX < 0 || m_tInfo.fX > WINCX || m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
        return DEAD;

    /*m_tInfo.fX = m_Pos.x;
    m_tInfo.fY = m_Pos.y;*/
    __super::Update();
    Move_Frame();

    return 0;
}

void CLightningProjectile::Render(HDC hDC)
{
    if (m_bDead) return;

    if (m_tInfo.fX < 0 || m_tInfo.fX > WINCX || m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
        return;
    
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    if (!hMemDC) return;

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

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

void CLightningProjectile::OnHit(CAttackCollider* pCol)
{
	m_bDead = true;
}

void CLightningProjectile::Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed)
{
    m_tFrame.iStart = iStart;
    m_tFrame.iEnd = iEnd;
    m_tFrame.iMotion = iMotion;
    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = dwSpeed;
}

void CLightningProjectile::Set_Active(bool bActive) { m_bActive = bActive; }

bool CLightningProjectile::Is_Active() const { return m_bActive; }
