#pragma once
#include "CObj.h"
#include "CKeyMgr.h"

class CProjectile : public CObj
{
public:
    CProjectile(Vec2 pos, Vec2 dir);

    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Render(HDC hDC) override;
    virtual void OnHit(CAttackCollider* pCol) override;
    virtual void Release() override;
    virtual void Late_Update() override;

protected:
    Vec2 m_Pos;
    Vec2 m_Dir;
    float m_Speed = 300.f;
    float m_Elapsed = 0.f;
    float m_LifeTime = 2.0f;
};

