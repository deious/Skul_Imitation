#pragma once
#include "CObj.h"
#include "CBmpMgr.h"

class CUIPortrait : public CObj 
{
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
