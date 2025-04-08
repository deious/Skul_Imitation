#pragma once

#include "Define.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

public:
	HDC			Get_MemDC();

public:
	void		Load_Bmp(const TCHAR* pFilePath);
	void		Release();


private:
	HDC			m_hMemDC;

	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldbmp;
};
