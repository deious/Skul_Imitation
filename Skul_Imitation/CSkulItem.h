#pragma once
#include "CItem.h"

class CSkulItem : public CItem
{
public:
    CSkulItem(const wstring& _Key);
public:
    const TCHAR* Get_FrameKey() const override;

private:
    wstring m_sFrameKey;
};

