#pragma once

#include "CObj.h"

class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr& rhs) = delete;
	CObjMgr& operator=(CObj& rObj) = delete;
	~CObjMgr();

public:
	CObj*				Get_Player();
	CObj*				Get_Boss(int Bossid);
	CObj*				Get_Target(OBJID eID, CObj* pObj);
	list<CObj*>&		Get_ObjList(OBJID eID);

public:
	void				Add_Object(OBJID eID, CObj* pObj);
	void				Update();
	void				Late_Update();
	void				Add_UI(RENDERID eID, CObj* pObj);
	void				Render(HDC hDC);
	void				Release();

	void				Delete_Object(OBJID eID);

public:
	static CObjMgr*		Get_Instance();

	static void			Destroy_Instance();

private:
	list<CObj*>			m_ObjList[OBJ_END];
	list<CObj*>			m_RenderList[RENDER_END];

	static CObjMgr*		m_pInstance;


};
