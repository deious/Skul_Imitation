#pragma once
#include "CObj.h"

class CPlayer;

class CUISkul : public CObj
{
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_IconKey(CPlayer* pPlayer);
};

