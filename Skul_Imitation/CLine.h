#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	virtual ~CLine();

public:
	void		Render(HDC hDC);

public:
	const LINE& Get_Info() const;

private:
	LINE		m_tInfo;

};

