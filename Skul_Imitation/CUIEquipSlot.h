#pragma once
#include "CObj.h"
#include "CItem.h"

class CUIEquipSlot : public CObj
{
public:
    CUIEquipSlot();
    CUIEquipSlot(int slotIndex);
    virtual ~CUIEquipSlot();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Item(CItem* pItem);
    CItem* Get_Item() const;
    bool IsInSlot(const POINT& pt) const;

    void Set_Default(bool bDefault);

private:
    CItem* m_pItem = nullptr;
    bool m_bIsDefaultSlot = false;
    int m_iSlotSize = 27;
    int m_iIndex = 0;
};

