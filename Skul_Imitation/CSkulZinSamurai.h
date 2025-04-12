#pragma once
#include "CSkulHead.h"
class CSkulZinSamurai :public CSkulHead
{
public:
	CSkulZinSamurai();
	virtual ~CSkulZinSamurai();

public:
	void UseSkillA(CPlayer* pPlayer) override;
	void UseSkillS(CPlayer* pPlayer) override;
	void UseSkillD(CPlayer* pPlayer) override;
	const wchar_t* Get_FrameKey(CPlayer* pPlayer) const override;
	const wchar_t* Get_IconKey() const override;
	const wstring Get_SkulId() const override;
	FRAME* Get_AllFrame() override;

private:
	int m_iSkillStep = 0;
	float m_fSkillTimer = 0.f;

	void SpawnSlashCollider(CPlayer* pPlayer);
};

