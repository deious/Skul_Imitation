#include "pch.h"
#include "CUIEquipSlot.h"
#include "CBmpMgr.h"
#include "CSkulItem.h"
#include "CSkulHead.h"
#include "CSkulSamurai.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CUIInventory.h"
#include "CUIMgr.h"

CUIEquipSlot::CUIEquipSlot() {}
CUIEquipSlot::CUIEquipSlot(int slotIndex) : m_iIndex(slotIndex)
{
    m_tInfo.fCX = 27.f;
    m_tInfo.fCY = 27.f;

    m_tInfo.fX = 550.f + slotIndex * 50.f;  // 좌우 간격
    m_tInfo.fY = 155.f;
    m_eRender = RENDER_UI;
}
CUIEquipSlot::~CUIEquipSlot() { Release(); }

void CUIEquipSlot::Initialize()
{
    m_eRender = RENDER_UI;
    m_tInfo.fCX = m_iSlotSize;
    m_tInfo.fCY = m_iSlotSize;
}

int CUIEquipSlot::Update()
{
    return 0;
}

void CUIEquipSlot::Late_Update() {}

void CUIEquipSlot::Render(HDC hDC)
{
    CUIInventory* pInventory = dynamic_cast<CUIInventory*>(CUIMgr::Get_Instance()->Find_UI(L"Inventory"));
    if (!pInventory || !pInventory->IsOpen()) return;

    RECT rc = {
        (int)(m_tInfo.fX - m_tInfo.fCX / 2),
        (int)(m_tInfo.fY - m_tInfo.fCY / 2),
        (int)(m_tInfo.fX + m_tInfo.fCX / 2),
        (int)(m_tInfo.fY + m_tInfo.fCY / 2)
    };

    //// 회색 테두리
    //HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));
    //HPEN hOldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(128, 128, 128)));
    //Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
    //DeleteObject(SelectObject(hDC, hOldPen));
    //SelectObject(hDC, hOldBrush);

    // 아이템 있으면 그리기
    if (m_pItem)
    {
        OutputDebugString(L"[EQUIP SLOT] 아이템 있음!\n");
        OutputDebugString(m_pItem->Get_FrameKey());
        HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pItem->Get_FrameKey());
        if (!hMemDC) return;

        GdiTransparentBlt(hDC,
            rc.left, rc.top,
            (int)m_tInfo.fCX, (int)m_tInfo.fCY,
            hMemDC, 0, 0,
            (int)m_tInfo.fCX, (int)m_tInfo.fCY,
            RGB(255, 0, 255));
    }
}

void CUIEquipSlot::Release()
{
    if (m_pItem)
    {
        delete m_pItem;
        m_pItem = nullptr;
    }
}

void CUIEquipSlot::Set_Item(CItem* pItem)
{
    if (m_bIsDefaultSlot)
    {
        m_pItem = pItem;
        return;
    }

    if (m_pItem)
        delete m_pItem;

    m_pItem = pItem;
    OutputDebugString(L"[CUIEquipSlot] 아이템 장착됨!\n");

    if (m_pItem && dynamic_cast<CSkulItem*>(m_pItem))
    {
        CSkulHead* pNewSkul = new CSkulSamurai();
        dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Skul(pNewSkul);
    }
}

CItem* CUIEquipSlot::Get_Item() const
{
    return m_pItem;
}

bool CUIEquipSlot::IsInSlot(const POINT& pt) const
{
    RECT rc = {
        (int)(m_tInfo.fX - m_tInfo.fCX / 2),
        (int)(m_tInfo.fY - m_tInfo.fCY / 2),
        (int)(m_tInfo.fX + m_tInfo.fCX / 2),
        (int)(m_tInfo.fY + m_tInfo.fCY / 2)
    };
    return PtInRect(&rc, pt);
}

void CUIEquipSlot::Set_Default(bool bDefault)
{
    m_bIsDefaultSlot = bDefault;
}