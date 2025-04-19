#pragma once
#include "CObj.h"
class CTrigger : public CObj
{
public:
	CTrigger(RECT area, std::function<void()> onTrigger);
	virtual ~CTrigger();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	RECT m_Area;
	bool m_bTriggered;
	std::function<void()> m_OnTrigger;
};

