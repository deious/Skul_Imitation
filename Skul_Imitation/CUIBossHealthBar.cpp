#include "pch.h"
#include "CUIBossHealthBar.h"
#include "CBoss.h"
#include "CObjMgr.h"
#include "CBmpMgr.h"

CUIBossHealthBar::CUIBossHealthBar(int bossId) : m_iBossId(bossId)
{
    m_tInfo.fCX = 212.f;
    m_tInfo.fCY = 22.f;

    if (m_iBossId == 0)
    {
        m_tInfo.fX = 169.f;
        m_tInfo.fY = 53.f;
    }
    else
    {
        m_tInfo.fX = 419.f;
        m_tInfo.fY = 53.f;
    }

    m_pFrameKey = L"BossHp_Bar";
    m_eRender = RENDER_UI;
}

CUIBossHealthBar::~CUIBossHealthBar()
{
}

void CUIBossHealthBar::Initialize()
{
}

int CUIBossHealthBar::Update()
{
    return 0;
}

void CUIBossHealthBar::Late_Update()
{
}

void CUIBossHealthBar::Render(HDC hDC)
{
    int curHp = dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_Boss(m_iBossId))->Get_Hp();
    int maxHp = dynamic_cast<CBoss*>(CObjMgr::Get_Instance()->Get_Boss(m_iBossId))->Get_MaxHp();

    if (curHp <= 0)
        return;

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
    float ratio = ((float)(curHp) / maxHp);
    int length = (int)(m_tInfo.fCX * ratio);

    if (m_iBossId == 0)
    {
        int destX = (int)(m_tInfo.fX + (m_tInfo.fCX - length));
        int srcX = (int)(m_tInfo.fCX - length);

        GdiTransparentBlt(
            hDC,
            destX, (int)m_tInfo.fY,        
            length, (int)m_tInfo.fCY,      
            hMemDC,
            srcX, 0,                        
            length, (int)m_tInfo.fCY,
            RGB(255, 220, 255));
    }
    else
    {
        GdiTransparentBlt(hDC, 
            (int)m_tInfo.fX, (int)m_tInfo.fY,
            length, (int)m_tInfo.fCY,
            hMemDC,
            0, 0,
            length, (int)m_tInfo.fCY, 
            RGB(255, 220, 255));
    }

    //HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    //int textW = 60;
    //int textH = 12;
    //
    //int centerX = (int)(m_tInfo.fX + m_tInfo.fCX * 0.5f);
    //int centerY = (int)(m_tInfo.fY + m_tInfo.fCY * 0.5f);

    //RECT rcText = {
    //    centerX - textW / 2,
    //    centerY - textH / 2,
    //    centerX + textW / 2,
    //    centerY + textH / 2
    //};
    //
    //SetBkMode(hDC, TRANSPARENT);
    //SetTextColor(hDC, RGB(255, 255, 255));
    //DrawText(hDC, szHpText, -1, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //
    //SelectObject(hDC, hOldFont);
    //DeleteObject(hFont);
}

void CUIBossHealthBar::Release()
{
}