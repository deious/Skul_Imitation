#pragma once

#include "CObj.h"
#include "CBoss.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj* Create_Obj()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create_Obj(int _id)
	{
		CObj* pObj = new T;
		dynamic_cast<CBoss*>(pObj)->Set_ID(_id);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create_Obj(float _fX, float _fY, DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Direction(eDir);

		return pObj;
	}
};
