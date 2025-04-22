#include "pch.h"
#include "CUIInventory.h"
#include "CBmpMgr.h"
#include "CSkulItem.h"
#include "CKeyMgr.h"
#include "CMouse.h"
#include "CObjMgr.h"
#include "CUIMgr.h"
#include "CPlayer.h"
#include "CSkulSamurai.h"
#include "CUIEquipSlot.h"
#include "CPotionItem.h"

CUIInventory::CUIInventory()
{
    /*m_vecItems.push_back(new CSkulItem(L"SamuraiIcon"));
    m_vecItems.push_back(new CSkulItem(L"SamuraiIcon"));*/
}

CUIInventory::~CUIInventory()
{
}

void CUIInventory::Initialize()
{
    m_eRender = RENDER_UI;
    m_tInfo.fCX = 650.f;
    m_tInfo.fCY = 650.f;
}

int CUIInventory::Update()
{
    //CMouse* pMouse = dynamic_cast<CMouse*>(CObjMgr::Get_Instance()->Get_Mouse());
    CMouse* pMouse = dynamic_cast<CMouse*>(CUIMgr::Get_Instance()->Get_Mouse());
    if (!pMouse) return 0;

    POINT ptMouse = {
        (LONG)pMouse->Get_Info()->fX,
        (LONG)pMouse->Get_Info()->fY
        /*(LONG)pMouse->Get_Info()->fX,
        (LONG)pMouse->Get_Info()->fY*/
        /*(LONG)CObjMgr::Get_Instance()->Get_Mouse()->Get_Info()->fX,
    (LONG)CObjMgr::Get_Instance()->Get_Mouse()->Get_Info()->fY*/
        /*(LONG)CUIMgr::Get_Instance()->Get_Mouse()->Get_Info()->fX,
    (LONG)CUIMgr::Get_Instance()->Get_Mouse()->Get_Info()->fY*/
        /*(LONG)pMouse->Get_Info()->fX + (LONG)CCameraMgr::Get_Instance()->Get_ScrollX(),
    (LONG)pMouse->Get_Info()->fY + (LONG)CCameraMgr::Get_Instance()->Get_ScrollY()*/
    };

    if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
    {
        for (size_t i = 0; i < m_vecItems.size(); ++i)
        {
            int row = static_cast<int>(i / 3);
            int col = static_cast<int>(i % 3);

            RECT rcSlot = {
                m_ptStartPos.x + 20 + col * m_iSlotSize,
                m_ptStartPos.y + 182 + row * m_iSlotSize,
                m_ptStartPos.x + 20 + col * m_iSlotSize + m_iSlotSize,
                m_ptStartPos.y + 182 + row * m_iSlotSize + m_iSlotSize
            };

            if (PtInRect(&rcSlot, ptMouse))
            {
                m_pSelectedItem = m_vecItems[i];
                m_bDragging = true;

                m_ptDragOffset.x = ptMouse.x - (rcSlot.left + m_iSlotSize / 2);
                m_ptDragOffset.y = ptMouse.y - (rcSlot.top + m_iSlotSize / 2);
                break;
            }
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
    {
        if (m_bDragging && m_pSelectedItem)
        {
            POINT ptMouse = {
            (LONG)pMouse->Get_Info()->fX,
            (LONG)pMouse->Get_Info()->fY
            };

            for (CObj* pUI : CUIMgr::Get_Instance()->Get_UIList())
            {
                CUIEquipSlot* pEquipSlot = dynamic_cast<CUIEquipSlot*>(pUI);
                if (!pEquipSlot) continue;

                if (pEquipSlot->IsInSlot(ptMouse))
                {
                    pEquipSlot->Set_Item(m_pSelectedItem);

                    // 인벤토리에서 제거
                    auto it = std::find(m_vecItems.begin(), m_vecItems.end(), m_pSelectedItem);
                    if (it != m_vecItems.end())
                        m_vecItems.erase(it);
                    break;
                }
            }
        }
        m_bDragging = false;
        m_pSelectedItem = nullptr;
    }

    if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
    {
        for (size_t i = 0; i < m_vecItems.size(); ++i)
        {
            int row = static_cast<int>(i / 3);
            int col = static_cast<int>(i % 3);

            RECT rcSlot = {
                m_ptStartPos.x + 20 + col * m_iSlotSize,
                m_ptStartPos.y + 182 + row * m_iSlotSize,
                m_ptStartPos.x + 20 + col * m_iSlotSize + m_iSlotSize,
                m_ptStartPos.y + 182 + row * m_iSlotSize + m_iSlotSize
            };

            POINT ptMouse = {
                (LONG)CUIMgr::Get_Instance()->Get_Mouse()->Get_Info()->fX,
                (LONG)CUIMgr::Get_Instance()->Get_Mouse()->Get_Info()->fY
            };

            if (PtInRect(&rcSlot, ptMouse))
            {
                if (CPotionItem* pPotion = dynamic_cast<CPotionItem*>(m_vecItems[i]))
                {
                    CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
                    if (pPlayer)
                    {
                        pPlayer->Heal(pPotion->Get_HealAmount());
                    }

                    // 인벤토리에서 삭제
                    Safe_Delete(m_vecItems[i]);
                    m_vecItems.erase(m_vecItems.begin() + i);
                }

                break;
            }
        }
    }

    if (CKeyMgr::Get_Instance()->Key_Down('I'))
        ToggleInventory();

    return 0;
}

void CUIInventory::Late_Update() {}

void CUIInventory::Render(HDC hDC)
{
    if (!m_bOpen)
    {
        return;
    }

    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Inventory");
    if (hMemDC)
    {
        const POINT& pt = m_ptStartPos;

        GdiTransparentBlt(
            hDC,
            pt.x, pt.y,
            m_tInfo.fCX, m_tInfo.fCY,
            hMemDC,
            0, 0,
            m_tInfo.fCX, m_tInfo.fCY,
            RGB(255, 0, 255));
    }

    int startX = m_ptStartPos.x + 20;
    int startY = m_ptStartPos.y + 182;
    int cols = 3;

    for (size_t i = 0; i < m_vecItems.size(); ++i)
    {
        if (m_vecItems[i] == m_pSelectedItem && m_bDragging)
            continue;

        int row = static_cast<int>(i / cols);
        int col = static_cast<int>(i % cols);

        int x = startX + col * m_iSlotSize;
        int y = startY + row * m_iSlotSize;

        const TCHAR* frameKey = m_vecItems[i]->Get_FrameKey();
        HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(frameKey);
        if (!hMemDC) continue;

        GdiTransparentBlt(
            hDC, x, y,
            27, 27,
            hMemDC, 0, 0,
            27, 27,
            RGB(255, 0, 255));
    }

    if (m_bDragging && m_pSelectedItem)
    {
        HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pSelectedItem->Get_FrameKey());
        if (hMemDC)
        {
            POINT pt = {
                /*(LONG)(CObjMgr::Get_Instance()->Get_Mouse()->Get_Info()->fX - m_ptDragOffset.x),
                (LONG)(CObjMgr::Get_Instance()->Get_Mouse()->Get_Info()->fY - m_ptDragOffset.y)*/
                (LONG)(CUIMgr::Get_Instance()->Get_Mouse()->Get_Info()->fX - m_ptDragOffset.x),
                (LONG)(CUIMgr::Get_Instance()->Get_Mouse()->Get_Info()->fY - m_ptDragOffset.y)
            };

            GdiTransparentBlt(hDC,
                pt.x, pt.y,
                m_iSlotSize, m_iSlotSize,
                hMemDC, 0, 0,
                m_iSlotSize, m_iSlotSize,
                RGB(255, 0, 255));
        }
    }
}

void CUIInventory::AddItem(CItem* pItem)
{
    m_vecItems.push_back(pItem);
}

void CUIInventory::ToggleInventory()
{
    m_bOpen = !m_bOpen;
}

void CUIInventory::AwakenSkul()
{
    delete m_pEquippedSkul;

    // 새로운 스컬 아이템으로 교체
    m_pEquippedSkul = new CSkulItem(L"ZinSamurai_Item");

    // 플레이어에도 새로운 스컬 장착
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
    if (pPlayer)
    {
        pPlayer->Set_Awaken();
    }

    //if (m_pEquippedSkul->Get_FrameKey() == L"Samurai_Item")
    //{
    //    // 기존 스컬은 delete 또는 처리 후
    //    delete m_pEquippedSkul;

    //    // 새로운 스컬 아이템으로 교체
    //    m_pEquippedSkul = new CSkulItem(L"ZinSamurai_Item");

    //    // 플레이어에도 새로운 스컬 장착
    //    CPlayer* pPlayer = dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player());
    //    if (pPlayer)
    //    {
    //        pPlayer->Set_Awaken();
    //    }
    //}
}

bool CUIInventory::IsOpen() const
{
    return m_bOpen;
}

void CUIInventory::Release() {}
