#include "CBoss.h"
#include "CBossWaitState.h"
#include "CBossDashAttack.h"
#include "CBossDuoDashFromEdge.h"
#include "CBossDuoDive.h"
#include "CBossDuoShootingLightning.h"
#include "CBossIdleState.h"
#include "IState.h"
#include "EBossStateType.h"
#include "CRandomMgr.h"

static int g_iNextWaitBossID = -1;
//static EBossStateType g_eNextTeamPattern = EBossStateType::None;
static bool g_bTeamPatternTime = false;

class CBossController
{
public:
    void Initialize(CBoss* a, CBoss* b);
    void Update();

private:
    IState<CBoss>* CreateTeamPattern(int index)
    {
        switch (index)
        {
        case 0: return new CBossDuoDashFromEdge();
        case 1: return new CBossDuoDive();
        case 2: return new CBossDuoShootingLightning();
        default: return new CBossDashAttack();
        }
    }

private:
    CBoss* m_pBossA = nullptr;
    CBoss* m_pBossB = nullptr;

    int iNum = 0;

    bool m_bDidFirstTeamPattern = false;
    bool m_bScheduledSecondBoss = false;
    float m_fTimer = 0.f;
    float m_fSoloCooldown = 0.f;
    float m_fSecondBossDelay = 0.f;
    float m_fSecondBossTimer = 0.f;
};