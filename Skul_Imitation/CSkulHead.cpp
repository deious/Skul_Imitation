#include "pch.h"
#include "CSkulHead.h"
#include "CObjMgr.h"
#include "CEffectMgr.h"
#include "CPlayer.h"

void CSkulHead::PlayHitEffect() const
{
	if (auto pPlayer = CObjMgr::Get_Instance()->Get_Player())
		CEffectMgr::Get_Instance()->Add_Effect(m_tEffectSet.tHitEffect, { pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY });
}

void CSkulHead::PlayDashEffect() const
{
	if (auto pPlayer = CObjMgr::Get_Instance()->Get_Player())
	{
		if (dynamic_cast<CPlayer*>(pPlayer)->Get_Direction() > 0)
		{
			CEffectMgr::Get_Instance()->Add_Effect(m_tEffectSet.tRDashEffect, { pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY });
		}
		else
		{
			CEffectMgr::Get_Instance()->Add_Effect(m_tEffectSet.tLDashEffect, { pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY });
		}
	}
}

void CSkulHead::PlayJumpEffect() const
{
	if (auto pPlayer = CObjMgr::Get_Instance()->Get_Player())
		CEffectMgr::Get_Instance()->Add_Effect(m_tEffectSet.tJumpEffect, { pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY });
}

void CSkulHead::PlayDieEffect() const
{
	if (auto pPlayer = CObjMgr::Get_Instance()->Get_Player())
		CEffectMgr::Get_Instance()->Add_Effect(m_tEffectSet.tDieEffect, { pPlayer->Get_Info()->fX, pPlayer->Get_Info()->fY });
}

const EffectInfo& CSkulHead::GetPlayAttackEffect() const
{
	if (auto pPlayer = CObjMgr::Get_Instance()->Get_Player())
	{
		if (dynamic_cast<CPlayer*>(pPlayer)->Get_Direction() > 0)
		{
			return m_tEffectSet.tRAttackEffect;
		}
		else
		{
			return m_tEffectSet.tLAttackEffect;
		}
	}
}

const EffectInfo& CSkulHead::GetPlaySkillAEffect() const
{
	return m_tEffectSet.tSkillAEffect;
}

const EffectInfo& CSkulHead::GetPlaySkillSEffect() const
{
	return m_tEffectSet.tSkillBEffect;
}
