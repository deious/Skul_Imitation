#include "pch.h"
#include "CUIWallet.h"

void CUIWallet::Initialize()
{
}

int CUIWallet::Update()
{
    return 0;
}

void CUIWallet::Late_Update()
{
}

void CUIWallet::Render(HDC hDC)
{
    //std::wstring goldText = L"Gold: " + std::to_wstring(m_iGold);
    //std::wstring crystalText = L"Crystal: " + std::to_wstring(m_iCrystal);

    int x = WINCX - 150;
    int y = WINCY - 80;

    SetTextColor(hDC, RGB(255, 215, 0));
    //TextOut(hDC, x, y, goldText.c_str(), (int)goldText.length());

    SetTextColor(hDC, RGB(100, 255, 255));
    //TextOut(hDC, x, y + 20, crystalText.c_str(), (int)crystalText.length());
}

void CUIWallet::Release()
{
}

void CUIWallet::SetGold(int gold) { m_iGold = gold; }

void CUIWallet::SetCrystal(int crystal) { m_iCrystal = crystal; }
