#include "pch.h"
#include "CKnightMonster.h"
#include "CAttackCollider.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CSoundMgr.h"
#include "CBmpMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"
#include "CLineMgr.h"
#include "CTileMgr.h"
#include "CCollisionMgr.h"
#include "CEffectMgr.h"

CKnightMonster::CKnightMonster() {}
CKnightMonster::~CKnightMonster() {}

void CKnightMonster::Initialize()
{
    m_pFrameKey = L"Knight_Left";
    m_iDamage = 10;
    m_iHp = 50;
    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 100.f;
    m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 30.f, 40.f);
    m_fMoveSpeed = 60.f;
    m_eRender = RENDER_GAMEOBJECT;
    BuildBehaviorTree();

    EffectInfo effect;
    effect.eType = EFFECT_TYPE::SKILLA;
    effect.sFramekey = L"Monster_Appear";
    effect.vOffset;
    effect.vSize = Vec2(150.f, 150.f); // ÀÌÆåÆ® Å©±â
    effect.iStartFrame = 0;
    effect.iEndFrame = 10;
    effect.iFrameSpeed = 50;
    effect.fScale = 1.f;
    effect.fRotation = 0.f;

    CEffectMgr::Get_Instance()->Add_Effect(effect, { m_tInfo.fX, m_tInfo.fY });
}

int CKnightMonster::Update()
{
    m_fSpawnTime += DELTA_TIME;

    if (m_bDead)
        return DEAD;

    if (m_pBehaviorTree)
        m_pBehaviorTree->Run();

    if (m_bAttack)
    {
        m_fAttackTimer += DELTA_TIME;
        if (m_fAttackTimer >= 1.2f)
        {
            m_bAttack = false;
            m_fAttackTimer = 0.f;
        }
    }

    __super::Update_Rect();
    Move_Frame();

    return 0;
}

void CKnightMonster::Attack()
{
    if (m_bAttack) return;

    m_bAttack = true;
    m_iPrevMotion = MOTION_ATTACK;

    if (m_eDir == DIR_LEFT)
        m_pFrameKey = L"Knight_Left";
    else
        m_pFrameKey = L"Knight_Right";

    Set_Frame(0, 3, 2, 300);

    CAttackCollider* pCol = new CAttackCollider(
        this,
        m_tInfo.fX + ((m_eDir == DIR_RIGHT) ? 20.f : -20.f),
        m_tInfo.fY,
        50.f, 30.f,
        0.f, 0.3f,
        CAttackCollider::ColliderType::Static,
        ETeam::Enemy,
        ESkillType::Attack,
        m_iDamage
    );
    pCol->Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_COLLIDER, pCol);

    //CSoundMgr::Get_Instance()->Play(L"monster_attack.wav");
}

void CKnightMonster::BuildBehaviorTree()
{
    auto* root = new SelectorNode();

    auto* attackSeq = new SequenceNode();
    attackSeq->AddChild(new ConditionNode([this]() {
        if (m_fSpawnTime < m_fAttackDelayAfterSpawn)
            return false;

        CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
        if (!pPlayer) return false;

        if (m_bAttack) return false;

        float dx = pPlayer->Get_Info()->fX - m_tInfo.fX;
        float dy = pPlayer->Get_Info()->fY - m_tInfo.fY;
        float distSq = dx * dx + dy * dy;
        return distSq <= 10.f * 10.f;
        }));
    attackSeq->AddChild(new ActionNode([this]() {
        this->Attack();
        }));

    root->AddChild(attackSeq);
    root->AddChild(new ActionNode([this]() {
        this->MoveRandom();
        }));

    m_pBehaviorTree = root;
}

void CKnightMonster::MoveRandom()
{
    if (m_bHit || m_bAttack) return;
    if (m_iPrevMotion != MOTION_WALK)
    {
        Set_Frame(0, 7, 1, 80);
        m_iPrevMotion = MOTION_WALK;
    }

    m_fMoveTimer += DELTA_TIME;
    if (m_fMoveTimer >= m_fChangeDirTime)
    {
        m_fMoveDir = (rand() % 2 == 0) ? -1.f : 1.f;
        m_fChangeDirTime = 2.f + static_cast<float>(rand()) / RAND_MAX * 2.f;
        m_fMoveTimer = 0.f;
    }

    if (m_bWallCollision)
    {
        m_fMoveDir *= -1.f;
        m_bWallCollision = false;
    }

    m_eDir = (m_fMoveDir < 0) ? DIR_LEFT : DIR_RIGHT;
    m_pFrameKey = (m_eDir == DIR_LEFT) ? L"Knight_Left" : L"Knight_Right";
}
