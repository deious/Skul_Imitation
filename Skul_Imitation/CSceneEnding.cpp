#include "pch.h"
#include "CSceneEnding.h"
#include "CSoundMgr.h"
#include "CTimeMgr.h"

void CSceneEnding::Initialize()
{
    m_vecCredits = {
        L"�����մϴ�!",
        L"",
        L"",
        L"",
        L"���α׷���: ���Ѽ�",
        L"",
        L"",
        L"",
        L"",
        L"Special Thanks",
        L"",
        L"��ȯ ������",
        L"����",
        L"��ȯ",
        L"����",
        L"����",
        L"����",
        L"����",
        L"�μ�",
        L"����",
        L"��ȣ",
        L"����",
        L"�ؼ�",
        L"��ȣ",
        L"�׸���",
        L"",
        L"",
        L"",
        L"",
        L"�̰� ���Ѻ��� ���",
        L"",
        L"",
        L"",
        L"",
        L"THE END"
    };

    m_fScrollY = WINCY + 50.f; // �Ʒ����� ����
    m_dwStartTime = GetTickCount64();

    // BGM ���� (���ϴ� ���� �̸�����)
    CSoundMgr::Get_Instance()->StopBGM();
    CSoundMgr::Get_Instance()->PlayBGM(L"Talesweaver.mp3");
}

int CSceneEnding::Update()
{
    m_fScrollY -= 40.f * DELTA_TIME;

    // 15�� �� ���� �Ǵ� Ű �Է� �� ����
    if (GetTickCount64() - m_dwStartTime > 45000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        PostQuitMessage(0); // ���� ����
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
        L"./Image/Font/PF��Ÿ����Ʈ.ttf"
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
