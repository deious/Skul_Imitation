#pragma once

#include "CObj.h"

class CCollisionMgr
{
public:
	static void	Collision_Rect(list<CObj*> DstList, list<CObj*> SrcList);
	static void	Collision_Circle(list<CObj*> DstList, list<CObj*> SrcList);
	static bool Check_Circle(CObj* pDst, CObj* pSrc);


	static void	Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList);
	static bool Check_Rect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight);
};

