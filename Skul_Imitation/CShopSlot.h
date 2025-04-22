#pragma once
#include "CObj.h"
#include "CItem.h"

enum class EItemType { SKUL, HEAL };

class CShopSlot : public CObj
{
public:
    CShopSlot();
    CShopSlot(wstring itemKey);
    virtual ~CShopSlot();

    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Late_Update() override;
    void Release() override;
    bool IsPurchased() const;

    void SetItem(CItem* pItem, const std::wstring& sKey);

private:
    CItem* m_pItem;
    bool m_bPurchased = false;
    bool m_bMovingUp = true;
    float m_fAnimOffset = 0.f;
    wstring m_sItemKey;
};