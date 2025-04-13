#pragma once
#include "pch.h"
#include "CObj.h"
#include "Define.h"

enum class ETeam
{
    Player,
    Enemy,
    Head
};

class CAttackCollider : public CObj
{
public:
    enum class ColliderType
    {
        Static,     // 고정
        Follow      // 주인 따라감
    };

    CAttackCollider(CObj* pOwner, float x, float y, float width, float height,
        float delay, float duration, ColliderType type, ETeam team, int damage);

    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    bool IsActive() const;
    ETeam Get_Team() const;
    int Get_Damage() const;
    bool Get_Hit(CObj* pTarget) const;
    void Insert_Hit(CObj* pTarget);

private:
    CObj* m_pOwner;

    float m_fElapsedTime;
    float m_fDelay;
    float m_fDuration;

    ColliderType m_eType;
    ETeam m_eTeam;
    int m_iDamage;
    bool m_bActive;

    unordered_set<CObj*> m_HitTargets;
};