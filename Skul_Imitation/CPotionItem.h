#pragma once
#include "CItem.h"

class CPotionItem : public CItem
{
public:
    CPotionItem(const std::wstring& key);
    virtual ~CPotionItem();
    const TCHAR* Get_FrameKey() const override;

    int Get_HealAmount();

private:
    std::wstring m_sFrameKey;
    int m_iHealAmount = 50;
};

