#pragma once
#include "CObj.h"
class CUIBossPortrait : public CObj
{
public:
    CUIBossPortrait();
    virtual ~CUIBossPortrait();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

};

