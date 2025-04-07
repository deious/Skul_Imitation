#include "pch.h"
#include "CLineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

bool CLineMgr::Collision_Line(float _fX, float* pY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& pLine : m_Linelist)
	{
		if (_fX >= pLine->Get_Info().tLeft.fX &&
			_fX <= pLine->Get_Info().tRight.fX)
		{
			pTargetLine = pLine;
		}
	}

	if (!pTargetLine)
		return false;


	// Y - y1 = ((y2 - y1 / x2- x1)) * (X - x1)
	// Y = ((y2 - y1 / x2 - x1)) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tLeft.fX;
	float	y1 = pTargetLine->Get_Info().tLeft.fY;

	float	x2 = pTargetLine->Get_Info().tRight.fX;
	float	y2 = pTargetLine->Get_Info().tRight.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

void CLineMgr::Load_Line()
{
	HANDLE	hFile = CreateFile(L"../Data/Line.dat", // ���� �̸��� ������ ���
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

	LINE	tLine{};

	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tLine.tLeft, tLine.tRight));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, L"�ҷ����� ����", _T("����"), MB_OK);
}

void CLineMgr::Initialize()
{
	Load_Line();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_Linelist)
		pLine->Render(hDC);

}

void CLineMgr::Release()
{
	for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
	m_Linelist.clear();
}
