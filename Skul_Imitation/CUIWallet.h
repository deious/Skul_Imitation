#pragma once
#include "CObj.h"
class CUIWallet : public CObj
{
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
    void SetGold(int gold);
    void SetCrystal(int crystal);

private:
    int m_iGold = 0;
    int m_iCrystal = 0;
};

