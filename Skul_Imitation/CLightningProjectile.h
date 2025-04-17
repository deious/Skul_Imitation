#pragma once
#include "CProjectile.h"
#include "CBmpMgr.h"
class CLightningProjectile : public CProjectile
{
public:
    CLightningProjectile(Vec2 pos, Vec2 dir, int iBossId);
    int Update() override;
    void Render(HDC hDC) override;
    void OnHit(CAttackCollider* pCol) override;

    void Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed);
    void Set_Active(bool bActive);
    bool Is_Active() const;

private:
    Vec2 m_vDir;
    wstring m_sEffectKey;
    bool m_bActive = false;
    int m_iBossId;
};

