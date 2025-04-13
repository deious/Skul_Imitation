#pragma once
#include "CScene.h"
class CBossStage : public CScene
{
public:
	CBossStage();
	virtual ~CBossStage();

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

private:
	void		Key_Input();
};
