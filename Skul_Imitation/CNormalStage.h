#pragma once
#include "CScene.h"
class CNormalStage : public CScene
{
public:
	CNormalStage();
	virtual ~CNormalStage();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void		Key_Input();
};

