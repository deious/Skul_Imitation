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
	CObj* Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }

	CObj* Get_Target(OBJID eID, CObj* pObj);


public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Delete_Object(OBJID eID);

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderList[RENDER_END];

	static CObjMgr* m_pInstance;


};
