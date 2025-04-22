#pragma once
#include "CObj.h"
#include "CAttackCollider.h"
#include "BehaviorNode.h"
#include "IState.h"
#include "CHitBox.h"

extern bool g_bIsTeamPatternTime;
extern float g_fTeamPatternTimer;
extern int g_iTeamPatternIndex;
extern int g_iWaitingBossID;
extern bool g_bTeamPatternStarted;

enum class EState 
{
    Idle,
    Move,
    Attack,
    Hit,
    Die,
    Awanken
};

class CBossController;

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
    void BuildSoloBehaviorTree();
    void CheckAndUpdateBehaviorTree();
    void OnHit(int damage) override;
    void Apply_Gravity();
    void Recovery();

    bool IsAwakened() const;
    bool IsDead() const;
    bool IsCheck() const;
    bool ShouldSyncAttack() const;

    int   Get_ID();
    int   Get_Hp();
    int   Get_MaxHp();
    float Get_Speed();
    CBoss* Get_PairBoss() const;
    EBossStateType Get_CurStateType() const;

    void Set_ID(int id);
    void Set_Speed(float fSpeed);
    void Set_PairBoss(CBoss* pOther);
    void Set_Frame(int iStart, int iEnd, int iMotion, DWORD dwSpeed);
    void Set_FrameKey(const TCHAR* pKey);
    void Set_Gravity();
    void Set_Controller(CBossController* pController);
    void Set_Invincibility(bool b);
    bool Move_Frame() override;
    bool Is_AnimFinished();
    bool Set_AnimStatus(bool state);
    void Set_AnimFinish() override;
    void Set_Awaken();

    CBossController* Get_Controller() const;

private:
    int m_iBossID = 0;
    int m_iHp;
    int m_iMaxHp = 1000;

    float		m_fGravity = 0.f;
    float       m_fAITimer = 0.f;
    float       m_fSpeed = 0.f;

    CBoss* m_pPairBoss;
    BehaviorNode* m_pAI = nullptr;
    IState<CBoss>* m_pCurState = nullptr;

    CBossController* m_pController = nullptr;

    bool m_bAwakened = false;
    bool m_bAwakening = false;
    bool		m_bUseGravity = true;
    bool m_bShowHitText = false;
    bool m_bIsDead = false;
    bool m_bUseTeamTree = true;
    bool m_binvincibility = false;
    bool m_bAnimed = false;
    ULONGLONG m_dwHitTime = 0;

    //CHitBox m_HitBox;

    const float GRAVITY_ACCEL = 0.5f;
    const float GRAVITY_MAX = 10.f;
};

