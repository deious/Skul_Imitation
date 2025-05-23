#include "pch.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CBoss.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Player() 
{
	if (m_ObjList[OBJ_PLAYER].empty())
		return nullptr;
	return m_ObjList[OBJ_PLAYER].front(); 
}

CObj* CObjMgr::Get_Boss(int id)
{
	if (m_ObjList[OBJ_BOSS].empty())
		return nullptr;
	for (auto iter = m_ObjList[OBJ_BOSS].begin();
		iter != m_ObjList[OBJ_BOSS].end(); )
	{
		if (dynamic_cast<CBoss*>(*iter)->Get_ID() == id)
		{
			return *iter;
		}
		else
		{
			iter++;
		}
	}
}

CObj* CObjMgr::Get_Mouse()
{
	if (!m_ObjList[OBJ_MOUSE].empty())
		return m_ObjList[OBJ_MOUSE].front();
	return nullptr;
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float fDistance(0.f);

	for (auto& Dst : m_ObjList[eID])
	{
		if (Dst->Get_Dead())
			continue;

		float		fWidth = Dst->Get_Info()->fX - pObj->Get_Info()->fX;
		float		fHeight = Dst->Get_Info()->fY - pObj->Get_Info()->fY;

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Dst;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

list<CObj*>& CObjMgr::Get_ObjList(OBJID eID)
{
	return m_ObjList[eID];
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if ((OBJ_END <= eID) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID eID = (*iter)->Get_RenderID();
			m_RenderList[eID].push_back(*iter);

		}
	}
	//CCollisionMgr::Collision_Circle(m_ObjList[OBJ_MOUSE], m_ObjList[OBJ_MONSTER]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
}

void CObjMgr::Add_UI(RENDERID eID, CObj* pObj)
{
	if ((RENDER_END <= eID) || (nullptr == pObj))
		return;

	m_RenderList[eID].push_back(pObj);
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->Get_Info()->fY < pSrc->Get_Info()->fY;
			});

		for (auto iter = m_RenderList[i].begin();
			iter != m_RenderList[i].end(); ++iter)
		{
			(*iter)->Render(hDC);
		}

		m_RenderList[i].clear();

		/*if (i != RENDER_MOUSE)
		{
			m_RenderList[i].sort([](CObj* pDst, CObj* pSrc)->bool
				{
					return pDst->Get_Info()->fY < pSrc->Get_Info()->fY;
				});
		}

		for (auto iter = m_RenderList[i].begin();
			iter != m_RenderList[i].end(); ++iter)
		{
			(*iter)->Render(hDC);
		}

		m_RenderList[i].clear();*/
	}
}

void CObjMgr::Release()
{
	/*for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}*/

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		m_ObjList[i].remove_if([](CObj* pObj) {
			if (pObj == CSceneMgr::Get_Instance()->Get_Player())
				return false;

			if (pObj->Get_Tag() == L"MOUSE")
				return false;

			Safe_Delete(pObj);
			return true;
			});
		//m_ObjList[i].remove(nullptr);
	}
}

void CObjMgr::Delete_Object(OBJID eID)
{
	for (auto& pObj : m_ObjList[eID])
	{
		Safe_Delete<CObj*>(pObj);
	}
	m_ObjList[eID].clear();
}

CObjMgr* CObjMgr::Get_Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CObjMgr;
	}

	return m_pInstance;
}

void CObjMgr::Destroy_Instance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
