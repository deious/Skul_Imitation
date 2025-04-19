#pragma once
#include "CMonster.h"
#include "BehaviorNode.h"

class CArcherMonster : public CMonster
{
public:
    CArcherMonster();
    virtual ~CArcherMonster();

    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    void BuildBehaviorTree();
    void Attack();
    void MoveRandom() override;

private:
    BehaviorNode* m_pBehaviorTree = nullptr;
    bool isInHorizontalRange;
    bool isOnSameLine;
    float m_fAttackDelayAfterSpawn = 1.5f;
    float m_fSpawnTime = 0.f;
    const float attackRange = 300.f;
    const float verticalTolerance = 30.f;
};

