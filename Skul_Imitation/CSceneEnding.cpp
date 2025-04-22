#include "pch.h"
#include "CSceneEnding.h"
#include "CSoundMgr.h"
#include "CTimeMgr.h"

void CSceneEnding::Initialize()
{
    m_vecCredits = {
        L"감사합니다!",
        L"",
        L"",
        L"",
        L"프로그래밍: 김한성",
        L"",
        L"",
        L"",
        L"",
        L"Special Thanks",
        L"",
        L"준환 선생님",
        L"누리",
        L"정환",
        L"진성",
        L"진우",
        L"찬빈",
        L"인혁",
        L"민석",
        L"현빈",
        L"선호",
        L"재훈",
        L"준석",
        L"진호",
        L"그리고",
        L"",
        L"",
        L"",
        L"",
        L"이걸 지켜봐준 당신",
        L"",
        L"",
        L"",
        L"",
        L"THE END"
    };

    m_fScrollY = WINCY + 50.f; // 아래에서 시작
    m_dwStartTime = GetTickCount64();

    // BGM 변경 (원하는 파일 이름으로)
    CSoundMgr::Get_Instance()->StopBGM();
    CSoundMgr::Get_Instance()->PlayBGM(L"Talesweaver.mp3");
}

int CSceneEnding::Update()
{
    m_fScrollY -= 40.f * DELTA_TIME;

    // 15초 후 종료 또는 키 입력 시 종료
    if (GetTickCount64() - m_dwStartTime > 45000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        PostQuitMessage(0); // 게임 종료
    }
    
    return 0;
}

void CSceneEnding::Late_Update()
{
}

void CSceneEnding::Render(HDC hDC)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT rc = { 0, 0, WINCX, WINCY };
    FillRect(hDC, &rc, hBrush);
    DeleteObject(hBrush);

    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));

    HFONT hFont = CreateFontW(
        -24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"./Image/Font/PF스타더스트.ttf"
    );

    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    for (size_t i = 0; i < m_vecCredits.size(); ++i)
    {
        int y = (int)m_fScrollY + (int)i * 40;
        TextOut(hDC, WINCX / 2 - 150, y, m_vecCredits[i].c_str(), m_vecCredits[i].length());
    }

    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
}

void CSceneEnding::Release()
{
}
