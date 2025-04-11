#include "pch.h"
#include "CTileMgr.h"
#include "CAbstractFactory.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CCameraMgr.h"
#include "CKeyMgr.h"


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
	/*for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float((TILECX >> 1) + (TILECX * j));
			float	fY = float((TILECY >> 1) + (TILECY * i));

			m_vecTile.push_back(CAbstractFactory<CTile>::Create_Obj(fX, fY));
		}
	}*/


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
	/*int iScrollX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
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
	}*/

	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();

	int startX = camRect.left / TILECX;
	int startY = camRect.top / TILECY;

	int endX = camRect.right / TILECX + 1;
	int endY = camRect.bottom / TILECY + 1;

	for (int i = startY; i < endY; ++i)
	{
		for (int j = startX; j < endX; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

	if (CKeyMgr::Get_Instance()->Get_ShowAll() && m_pQuadTree)
	{
		//MessageBox(g_hWnd, L"�����ֱ� ����", _T("Fail"), MB_OK);
		std::vector<Tile> debugTiles;
		m_pQuadTree->Query(camRect, debugTiles);
		//RECT fullMap = { 0, 0, TILEX * TILECX, TILEY * TILECY };
		//m_pQuadTree->Query(fullMap, debugTiles);

		for (const auto& tile : debugTiles) {
			/*int left = tile.x - TILECX / 2 -	(int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int top = tile.y - TILECY / 2 -		(int)CScrollMgr::Get_Instance()->Get_ScrollY();
			int right = tile.x + TILECX / 2 -	(int)CScrollMgr::Get_Instance()->Get_ScrollX();
			int bottom = tile.y + TILECY / 2 -	(int)CScrollMgr::Get_Instance()->Get_ScrollY();*/

			POINT lt = CCameraMgr::Get_Instance()->WorldToScreen(tile.x - TILECX / 2, tile.y - TILECY / 2);
			POINT rb = CCameraMgr::Get_Instance()->WorldToScreen(tile.x + TILECX / 2, tile.y + TILECY / 2);

			// �׸�
			Rectangle(hDC, lt.x, lt.y, rb.x, rb.y);

			// X��
			MoveToEx(hDC, lt.x, lt.y, NULL);
			LineTo(hDC, rb.x, rb.y);
			MoveToEx(hDC, rb.x, lt.y, NULL);
			LineTo(hDC, lt.x, rb.y);

			//int left = tile.x - TILECX / 2 + (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			//int top = tile.y - TILECY / 2 + (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			//int right = tile.x + TILECX / 2 + (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			//int bottom = tile.y + TILECY / 2 + (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			////MessageBox(g_hWnd, L"Ÿ�� ������?", _T("Fail"), MB_OK);

			//// �׸� �׸���
			//Rectangle(hDC, left, top, right, bottom);

			//// X�� �׸���
			//MoveToEx(hDC, left, top, NULL);
			//LineTo(hDC, right, bottom);

			//MoveToEx(hDC, right, top, NULL);
			//LineTo(hDC, left, bottom);
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

//void CTileMgr::Picking_Tile(POINT _pt, int _iDrawID, int _iOption)
//{
//	int		x = _pt.x / TILECX;
//	int	    y = _pt.y / TILECY;
//
//	int iIndex = y * TILEX + x;
//
//	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
//		return;
//
//	//dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
//	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
//
//}

//void CTileMgr::Save_Tile()
//{
//	HANDLE	hFile = CreateFile(L"./Data/Tile.dat", // ���� �̸��� ������ ���
//		GENERIC_WRITE,  // ���� �뵵(GENERIC_WRITE : ����(����), GENERIC_READ : �б�(�ҷ�����))
//		NULL,			// ���� ���(NULL�� ��� �������� ����)
//		NULL,			// ���� ����(NULL�� ��� �⺻������ ����)
//		CREATE_ALWAYS,	// ���� ���(CREATE_ALWAYS : ���� ����, OPEN_EXISTING : �б� ����)
//		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(����, �б� ���� ���� ��) : �ƹ��� �Ӽ��� ���� �Ϲ� ����
//		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ����(�Ⱦ����̱� ������ NULL)
//
//	if (hFile == INVALID_HANDLE_VALUE)
//	{
//		MessageBox(g_hWnd, L"Save File", _T("Fail"), MB_OK);
//		return;
//	}
//
//	DWORD	dwByte(0);
//	int iDrawID(0), iOption(0);
//
//	for (auto& pTile : m_vecTile)
//	{
//
//		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
//		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();
//
//		WriteFile(hFile, pTile->Get_Info(), sizeof(INFO), &dwByte, nullptr);
//		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
//		WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
//	}
//
//	CloseHandle(hFile);
//
//	MessageBox(g_hWnd, L"�����ϱ� ����", _T("����"), MB_OK);
//}

void CTileMgr::Load_Tile()
{
	HANDLE	hFile = CreateFile(L"./Data/map.dat", // ���� �̸��� ������ ���
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
	int x, y;
	//int		iDrawID(0);
	int		iOption(0);

	Release();
	RECT mapRect = { 0, 0, TILEX * TILECX, TILEY * TILECY };
	m_pQuadTree = new CQuadTree(mapRect, 10, 5);

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		//ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		//if (!ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr) || dwByte == 0) break;  -> �ӽ� �ּ�ó��
		//if (!ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr) || dwByte == 0) break;
		/*if (!ReadFile(hFile, &x, sizeof(int), &dwByte, nullptr) || dwByte == 0) break;
		if (!ReadFile(hFile, &y, sizeof(int), &dwByte, nullptr) || dwByte == 0) break;
		if (!ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr) || dwByte == 0) break;*/

		CObj* pTile = CAbstractFactory<CTile>::Create_Obj(tInfo.fX, tInfo.fY);
		//CObj* pTile = CAbstractFactory<CTile>::Create_Obj(x, y);
		//dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
		m_vecTile.push_back(pTile);

		/*wchar_t msg[100];
		swprintf_s(msg, 100, L"Tile ��ġ: (%d, %d), Ÿ��: %d", x, y, iOption);

		MessageBox(g_hWnd, msg, L"Ÿ�� �����", MB_OK);*/

		if (iOption == 1)
		{
			Tile tile = { (int)tInfo.fX, (int)tInfo.fY, iOption };
			//Tile tile = { x, y, iOption };
			m_pQuadTree->Insert(tile);
			//MessageBox(g_hWnd, L"�浹 Ÿ�� ����", _T("Fail"), MB_OK);
		}
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, L"�ҷ����� ����", _T("����"), MB_OK);
}

CTileMgr* CTileMgr::Get_Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CTileMgr;
	}

	return m_pInstance;
}

CQuadTree* CTileMgr::Get_Tree()
{
	return m_pQuadTree;
}

void CTileMgr::Destroy_Instance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CTileMgr::Set_ShowTile()
{
	m_bShowTile = !m_bShowTile;
}
