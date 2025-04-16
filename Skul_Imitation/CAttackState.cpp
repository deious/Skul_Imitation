#include "pch.h"
#include "CAttackState.h"
#include "CPlayer.h"
#include "CIdleState.h"
#include "CKeyMgr.h"
#include "CWalkState.h"
#include "CDashState.h"
#include "CJumpStartState.h"
#include "CObjMgr.h"
#include "CBoss.h"
#include "CEffectMgr.h"
#include "CSoundMgr.h"

CAttackState::CAttackState(int iCombo) : m_iCombo(iCombo)
{
}

void CAttackState::Enter(CPlayer* pPlayer)
{
    list<CObj*>& bossList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS);
    for (CObj* pObj : bossList)
    {
        if (!pObj || pObj->Get_Dead()) continue;

        CBoss* pBoss = dynamic_cast<CBoss*>(pObj);
        if (!pBoss) continue;

        CHitBox* pHitBox = pBoss->Get_HitBox();
        if (!pHitBox) continue;

        pHitBox->Reset_HitCount();
        pHitBox->Set_MaxHits(1);
    }
    m_dwLastAttackTime = GetTickCount64();

    int iStart, iEnd, iMotion;
    ULONGLONG dwFrameSpeed;
    if (pPlayer->Get_Skul()->Get_SkulId() == L"Normal")
        CSoundMgr::Get_Instance()->Play(L"Default_Attack.flac");
    else
        CSoundMgr::Get_Instance()->Play(L"Attack_Sound.wav");
    switch (m_iCombo)
    {
    case 0:
    {
        FRAME* tempFrame = pPlayer->Get_Skul()->Get_AllFrame();
        iStart = tempFrame[SKUL_ATTACK].iStart;
        iEnd = tempFrame[SKUL_ATTACK].iEnd;
        iMotion = tempFrame[SKUL_ATTACK].iMotion;
        dwFrameSpeed = tempFrame[SKUL_ATTACK].dwFrameSpeed;
        pPlayer->Set_Frame(iStart, iEnd, iMotion, dwFrameSpeed); break;
        //CEffectMgr::Get_Instance()->Add_Effect(pPlayer->Get_Skul()->GetPlayAttackEffect(), { pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY });
        //pPlayer->Set_Frame(0, 4, 6, 100); break; // 1타
    }
    case 1:
    {
        FRAME* tempFrame = pPlayer->Get_Skul()->Get_AllFrame();
        iStart = tempFrame[SKUL_ATTACK2].iStart;
        iEnd = tempFrame[SKUL_ATTACK2].iEnd;
        iMotion = tempFrame[SKUL_ATTACK2].iMotion;
        dwFrameSpeed = tempFrame[SKUL_ATTACK2].dwFrameSpeed;
        pPlayer->Set_Frame(iStart, iEnd, iMotion, dwFrameSpeed); break;
        //pPlayer->Set_Frame(0, 3, 7, 100); break; // 2타
    }
    case 2:
    {
        FRAME* tempFrame = pPlayer->Get_Skul()->Get_AllFrame();
        iStart = tempFrame[SKUL_ATTACK3].iStart;
        iEnd = tempFrame[SKUL_ATTACK3].iEnd;
        iMotion = tempFrame[SKUL_ATTACK3].iMotion;
        dwFrameSpeed = tempFrame[SKUL_ATTACK3].dwFrameSpeed;
        pPlayer->Set_Frame(iStart, iEnd, iMotion, dwFrameSpeed); break;
        //pPlayer->Set_Frame(0, 3, 8, 100); break; // 3타
    }
    }
}

void CAttackState::Update(CPlayer* pPlayer)
{
    if (CKeyMgr::Get_Instance()->Key_Down('X') && !m_bQueued)
        m_bQueued = true;

    // 콤보 유지시간 초과 시 초기화
    if (GetTickCount64() - m_dwLastAttackTime > COMBO_DELAY)
    {
        pPlayer->ChangeState(new CIdleState());
        return;
    }

    if (!m_bColliderSpawned && pPlayer->Get_CurFrame() == 2)
    {
        pPlayer->Create_AttackCollider(m_iCombo, 0);
        m_bColliderSpawned = true;
    }

    m_bAnimEnd = pPlayer->Move_Frame();

    if (m_bAnimEnd)
    {
        if (m_bQueued && m_iCombo < 2)
        {
            pPlayer->ChangeState(new CAttackState(m_iCombo + 1));
        }
        else
        {
            pPlayer->ChangeState(new CIdleState());
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) || CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
    {
        pPlayer->ChangeState(new CWalkState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('C') && !pPlayer->Get_IsJump())
    {
        pPlayer->ChangeState(new CJumpStartState());
        return;
    }

    if (CKeyMgr::Get_Instance()->Key_Down('Z') && pPlayer->Dash_Check())
    {
        pPlayer->Set_LastDashTime();
        pPlayer->ChangeState(new CDashState());
        return;
    }

    return;
}

void CAttackState::Exit(CPlayer* pPlayer)
{
    m_bQueued = false;
}

EPlayerState CAttackState::GetStateID() const
{
    return EPlayerState::ATTACK;
}
