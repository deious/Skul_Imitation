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
	HANDLE	hFile = CreateFile(L"../Data/Line.dat", // 파일 이름을 포함한 경로
		GENERIC_READ,  // 파일 용도(GENERIC_WRITE : 쓰기(저장), GENERIC_READ : 읽기(불러오기))
		NULL,			// 공유 방식(NULL인 경우 공유하지 않음)
		NULL,			// 보안 설정(NULL인 경우 기본값으로 설정)
		OPEN_EXISTING,	// 생성 방식(CREATE_ALWAYS : 쓰기 전용, OPEN_EXISTING : 읽기 전용)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(숨김, 읽기 전용 파일 등) : 아무런 속성이 없는 일반 형식
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일(안쓸것이기 때문에 NULL)

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

	MessageBox(g_hWnd, L"불러오기 성공", _T("성공"), MB_OK);
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
