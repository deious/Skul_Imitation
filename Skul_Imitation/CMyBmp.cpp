#include "pch.h"
#include "CMyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : ���� dc�� ȣȯ�Ǵ� dc�� �Ҵ��ϴ� �Լ�

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// ���α׷� �ν��Ͻ� �ڵ�(���Ϸκ��� �о�� ���̱� ������ null)
		pFilePath,	// ������ ���
		IMAGE_BITMAP,	 // � Ÿ���� �������� �ɼ� ����
		0, 0,			// �о���� ������ ����, ���� ������(���Ϸ� �о�鿩�� ũ�� �״�θ� ����� ���̱� ������ 0, 0)
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : ���Ϸκ��� �̹��� ���� �ҷ�����, LR_CREATEDIBSECTION : DIB �������� ���� ��ȯ

	// SelectObject : gdi ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);

}
