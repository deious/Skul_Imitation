#pragma once
#include "CProjectile.h"
#include "CMonster.h"

class CArrow : public CProjectile
{
public:
    CArrow(Vec2 pos, Vec2 dir, CMonster* pMonster);
    int Update() override;
    void Render(HDC hDC) override;
    void OnHit(CAttackCollider* pCol) override;

    void Set_Frame(int iStart, int iEnd, DWORD dwSpeed);
    void Set_Active(bool bActive);
    bool Is_Active() const;

private:
    Vec2 m_vDir;
    wstring m_sEffectKey;
    bool m_bActive = false;
};
