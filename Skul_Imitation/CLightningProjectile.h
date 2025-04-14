#pragma once
#include "CProjectile.h"
#include "CBmpMgr.h"
class CLightningProjectile : public CProjectile
{
public:
    CLightningProjectile(Vec2 pos, Vec2 dir);
    int Update() override;
    void Render(HDC hDC) override;
    void OnHit(CAttackCollider* pCol) override;
};

