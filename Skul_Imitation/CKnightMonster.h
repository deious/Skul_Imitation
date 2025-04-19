#pragma once
#include "CObj.h"
#include "BehaviorNode.h"
#include "CMonster.h"

class CKnightMonster : public CMonster
{
public:
	CKnightMonster();
	virtual ~CKnightMonster();

	void Initialize() override;
	int Update() override;
	void Attack() override;
	void BuildBehaviorTree();

	// CMonster을(를) 통해 상속됨
	void MoveRandom() override;

private:
	float m_fSpawnTime = 0.f;
	float m_fAttackDelayAfterSpawn = 1.5f;
};

