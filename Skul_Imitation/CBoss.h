#pragma once
#include "CObj.h"
#include "CAttackCollider.h"
#include "BehaviorNode.h"
#include "IState.h"
#include "CHitBox.h"

enum class EState 
{
    Idle,
    Move,
    Attack,
    Hit,
    Die,
};

class CBoss : public CObj
{
public:
    CBoss();
    virtual ~CBoss();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

    void ChangeState(IState<CBoss>* pNewState);
    void BuildBehaviorTree();
    void OnHit(CAttackCollider* pCol) override;

    void Apply_Gravity();

    bool IsAwakened() const;
    bool IsDead() const;
    bool ShouldSyncAttack() const;

    void Set_ID(int id);
    void Set_PairBoss(CBoss* pOther);
    void Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed);
    void Set_FrameKey(const TCHAR* pKey);

private:
    int m_iBossID = 0;
    int m_iHp;

    float		m_fGravity = 0.f;
    float       m_fAITimer = 0.f;

    CBoss* m_pPairBoss;
    BehaviorNode* m_pAI;
    IState<CBoss>* m_pCurState = nullptr;
    bool m_bAwakened;
    bool		m_bUseGravity = true;
    bool m_bShowHitText = false;
    ULONGLONG m_dwHitTime = 0;

    //CHitBox m_HitBox;

    const float GRAVITY_ACCEL = 0.5f;
    const float GRAVITY_MAX = 10.f;
};

