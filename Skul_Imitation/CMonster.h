#pragma once
#include "CObj.h"
#include "BehaviorNode.h"

enum MonsterMotion
{
    MOTION_IDLE,
    MOTION_WALK,
    MOTION_ATTACK,
    MOTION_HIT
};

class CMonster : public CObj
{
public:
    CMonster();
    virtual ~CMonster();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Attack() = 0;
    virtual void MoveRandom() = 0;

    virtual void OnHit(CAttackCollider* pCol);

    void OnHit(int damage) override;

protected:
    void Apply_Gravity();
    void Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed);

protected:
    bool    m_bHit = false;
    bool    m_bAttack = false;
    bool    m_bWallCollision = false;
    bool    m_bUseGravity = true;
    bool    m_bIsDead = false;

    float   m_fMoveTimer = 0.f;
    float   m_fChangeDirTime = 0.f;
    float   m_fMoveDir = 0.f;
    float   m_fMoveSpeed = 0.f;
    float   m_fGravity = 0.f;
    float   m_fAttackTimer = 0.f;

    int     m_iDamage = 10;
    int     m_iHp = 50;
    MonsterMotion m_iPrevMotion = MOTION_IDLE;
    BehaviorNode* m_pBehaviorTree = nullptr;

    const float GRAVITY_ACCEL = 0.5f;
    const float GRAVITY_MAX = 10.f;
};

