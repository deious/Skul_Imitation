#pragma once

#include "CObj.h"
#include "CQuadTree.h"

class CCollisionMgr
{
public:
	static void		Collision_Rect(list<CObj*> DstList, list<CObj*> SrcList);
	static void		Collision_Circle(list<CObj*> DstList, list<CObj*> SrcList);
	static void		Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList);
	
	static bool		Check_Circle(CObj* pDst, CObj* pSrc);
	static bool		Check_Rect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight);
	static bool		RectCollision(const RECT& rectA, const RECT& rectB);
	static void		Collision_Attack();
	static void		CheckHeadCollisionWithPlayer(CObj* pCollider, list<CObj*>& playerList);
	static void		CheckCollisionWithTargets(CObj* pCollider, list<CObj*>& targets);
	static void		PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree);
};

