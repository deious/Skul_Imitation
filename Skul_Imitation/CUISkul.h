#pragma once
#include "CObj.h"

class CPlayer;

class CUISkul : public CObj
{
public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_IconKey(CPlayer* pPlayer);
};

