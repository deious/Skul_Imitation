#pragma once
#include "CObj.h"
class CUIBossHealthBar : public CObj
{
public:
	CUIBossHealthBar(int iBossid);
	virtual ~CUIBossHealthBar();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iBossId;
};