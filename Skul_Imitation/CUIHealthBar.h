#pragma once
#include "CObj.h"

class CUIHealthBar : public CObj 
{
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void SetHP(int current, int max);

private:
    int m_iMaxHP = 100;
    int m_iCurrentHP = 100;
};

