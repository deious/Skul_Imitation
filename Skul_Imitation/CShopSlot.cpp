#include "pch.h"
#include "CShopSlot.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CBmpMgr.h"
#include "CUIInventory.h"
#include "CUIMgr.h"
#include "CSkulItem.h"
#include "CPotionItem.h"
#include "CTimeMgr.h"

CShopSlot::CShopSlot()
{
}

CShopSlot::CShopSlot(wstring itemKey)
    : m_bPurchased(false), m_bMovingUp(false), m_fAnimOffset(0.f), m_sItemKey(itemKey)
{
    m_tInfo.fCX = 27.f;
    m_tInfo.fCY = 27.f;
    m_eRender = RENDER_UI;
}

CShopSlot::~CShopSlot()
{
    Safe_Delete(m_pItem);
}

void CShopSlot::Initialize()
{
    m_tInfo.fCX = 27.f;
    m_tInfo.fCY = 27.f;
    m_eRender = RENDER_UI;
}

int CShopSlot::Update()
{
    if (m_bPurchased)
        return DEAD;

    float fSpeed = 20.f * DELTA_TIME;
    if (m_bMovingUp)
        m_fAnimOffset -= fSpeed;
    else
        m_fAnimOffset += fSpeed;

    if (m_fAnimOffset > 5.f) m_bMovingUp = true;
    if (m_fAnimOffset < -5.f) m_bMovingUp = false;

    // 충돌 감지
    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    if (!pPlayer) return 0;

    float dx = fabsf(pPlayer->Get_Info()->fX - m_tInfo.fX);
    float dy = fabsf(pPlayer->Get_Info()->fY - m_tInfo.fY);

    if (dx < 50.f && dy < 50.f)
    {
        if (CKeyMgr::Get_Instance()->Key_Down('F'))
        {
            CUIInventory* pInventory = dynamic_cast<CUIInventory*>(CUIMgr::Get_Instance()->Find_UI(L"Inventory"));
            CItem* pClonedItem = nullptr;

            if (dynamic_cast<CSkulItem*>(m_pItem))
                pClonedItem = new CSkulItem(m_sItemKey);
            else if (dynamic_cast<CPotionItem*>(m_pItem))
                pClonedItem = new CPotionItem(m_sItemKey);

            if (pClonedItem)
            {
                pInventory->AddItem(pClonedItem);
                m_bPurchased = true;
            }

            m_bPurchased = true;
        }
    }

    return 0;
}

void CShopSlot::Late_Update() {}

void CShopSlot::Render(HDC hDC)
{
    if (m_bPurchased || !m_pItem) return;

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_sItemKey.c_str());
    if (!hMemDC) return;

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)(m_tInfo.fY + m_fAnimOffset));
    GdiTransparentBlt(
        hDC,
        screen.x - (int)(m_tInfo.fCX * 0.5f),
        screen.y - (int)(m_tInfo.fCY * 0.5f),
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        hMemDC,
        0, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        RGB(255, 0, 255));
}

void CShopSlot::Release()
{
    Safe_Delete(m_pItem);
}

bool CShopSlot::IsPurchased() const { return m_bPurchased; }

void CShopSlot::SetItem(CItem* pItem, const std::wstring& sKey)
{
    m_pItem = pItem;
    m_sItemKey = sKey;
}
