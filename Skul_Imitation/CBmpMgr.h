#pragma once

#include "CMyBmp.h"

class CBmpMgr
{
private:
	CBmpMgr();
	virtual ~CBmpMgr();

public:
	void							Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC								Find_Image(const TCHAR* pImgKey);
	void							Release();

public:
	static CBmpMgr*					Get_Instance();
	static void						Destroy_Instance();

private:
	static CBmpMgr*					m_pInstance;
	map<const TCHAR*, CMyBmp*>		m_mapBit;
};

