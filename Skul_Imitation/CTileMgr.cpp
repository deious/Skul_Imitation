#include "pch.h"
#include "CTileMgr.h"
#include "CAbstractFactory.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"


CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float((TILECX >> 1) + (TILECX * j));
			float	fY = float((TILECY >> 1) + (TILECY * i));

			m_vecTile.push_back(CAbstractFactory<CTile>::Create_Obj(fX, fY));
		}
	}


}

void CTileMgr::Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& pTile : m_vecTile)
		pTile->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	int iScrollX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int iScrollY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	int iMaxX = iScrollX + WINCX / TILECX + 2;
	int iMaxY = iScrollY + WINCY / TILECY + 2;

	for (int i = iScrollY; i < iMaxY; ++i)
	{
		for (int j = iScrollX; j < iMaxX; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

	//for (auto& pTile : m_vecTile)
	//	pTile->Render(hDC);

}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(POINT _pt, int _iDrawID, int _iOption)
{
	int		x = _pt.x / TILECX;
	int	    y = _pt.y / TILECY;

	int iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);

}

void CTileMgr::Save_Tile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat", // ���� �̸��� ������ ���
		GENERIC_WRITE,  // ���� �뵵(GENERIC_WRITE : ����(����), GENERIC_READ : �б�(�ҷ�����))
		NULL,			// ���� ���(NULL�� ��� �������� ����)
		NULL,			// ���� ����(NULL�� ��� �⺻������ ����)
		CREATE_ALWAYS,	// ���� ���(CREATE_ALWAYS : ���� ����, OPEN_EXISTING : �б� ����)
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(����, �б� ���� ���� ��) : �ƹ��� �Ӽ��� ���� �Ϲ� ����
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ����̱� ������ NULL)

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Save File", _T("Fail"), MB_OK);
		return;
	}

	DWORD	dwByte(0);
	int iDrawID(0), iOption(0);

	for (auto& pTile : m_vecTile)
	{

		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"�����ϱ� ����", _T("����"), MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE	hFile = CreateFile(L"../Data/Tile.dat", // ���� �̸��� ������ ���
		GENERIC_READ,  // ���� �뵵(GENERIC_WRITE : ����(����), GENERIC_READ : �б�(�ҷ�����))
		NULL,			// ���� ���(NULL�� ��� �������� ����)
		NULL,			// ���� ����(NULL�� ��� �⺻������ ����)
		OPEN_EXISTING,	// ���� ���(CREATE_ALWAYS : ���� ����, OPEN_EXISTING : �б� ����)
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(����, �б� ���� ���� ��) : �ƹ��� �Ӽ��� ���� �Ϲ� ����
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ����̱� ������ NULL)

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"Load File", _T("Fail"), MB_OK);
		return;
	}

	DWORD	dwByte(0);

	INFO	tInfo{};

	int		iDrawID(0), iOption(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create_Obj(tInfo.fX, tInfo.fY);

		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

		m_vecTile.push_back(pTile);

	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"�ҷ����� ����", _T("����"), MB_OK);
}
