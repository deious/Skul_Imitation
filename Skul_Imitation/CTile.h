#pragma once

#include "CObj.h"
#include "Define.h"

class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	int			Get_Option();
	//int			Get_DrawID();

	//void		Set_DrawID(int iDrawID);
	void		Set_Option(int iOption);


public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

private:
	//int			m_iDrawID;
	int			m_iOption;

};
