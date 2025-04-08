#pragma once

#include "CTile.h"
#include "CQuadTree.h"

class CTileMgr
{
private:
	CTileMgr();
	virtual ~CTileMgr();

public:
	void				Initialize();
	void				Update();
	void				Late_Update();
	void				Render(HDC hDC);
	void				Release();

public:
	//void				Picking_Tile(POINT _pt, int _iDrawID, int _iOption);
	//void				Save_Tile();
	void				Load_Tile();

public:
	static CTileMgr*	Get_Instance();
	CQuadTree*			Get_Tree();
	static void			Destroy_Instance();
	void				Set_ShowTile();

private:
	static CTileMgr*	m_pInstance;
	vector<CObj*>		m_vecTile;
	CQuadTree*			m_pQuadTree = nullptr;
	bool				m_bShowTile = false;
};
