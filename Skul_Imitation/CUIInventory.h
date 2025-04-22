#pragma once
#include "CObj.h"
#include "CUIInventory.h"
#include "CItem.h"

class CUIInventory : public CObj
{
public:
    CUIInventory();
    virtual ~CUIInventory();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void AddItem(CItem* pItem);
    void ToggleInventory();
    void AwakenSkul();
    bool IsOpen() const;

private:
    std::vector<CItem*> m_vecItems;
    bool m_bOpen = false;
    bool   m_bDragging = false;
    int m_iSlotSize = 42;
    CItem* m_pSelectedItem = nullptr;
    POINT m_ptStartPos = { 100, -25 };
    POINT  m_ptDragOffset = { 0, 0 };
    CItem* m_pEquippedSkul = nullptr;
};