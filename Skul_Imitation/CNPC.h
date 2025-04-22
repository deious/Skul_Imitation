#pragma once
#include "CObj.h"
class CNPC :
    public CObj
{
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Activate(bool b);

private:
    bool m_bActive = false;
    bool m_bPlayerInRange = false;
    std::wstring m_sFrameKey = L"Spider";
};

