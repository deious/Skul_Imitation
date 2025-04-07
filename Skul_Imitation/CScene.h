#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Late_Update()PURE;	// UPDATE 연산이 끝난 이후
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

};
