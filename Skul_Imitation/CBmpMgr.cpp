#include "pch.h"
#include "CBmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
		{
			return !lstrcmp(pImgKey, MyPair.first);
		});

	if (iter == m_mapBit.end())
	{
		CMyBmp* pBmp = new CMyBmp;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}
}

HDC CBmpMgr::Find_Image(const TCHAR* pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
		{
			return !lstrcmp(pImgKey, MyPair.first);
		});

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}

CBmpMgr* CBmpMgr::Get_Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CBmpMgr;
	}

	return m_pInstance;
}

void CBmpMgr::Destroy_Instance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
