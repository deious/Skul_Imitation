#pragma once
#include "CObj.h"
class CTutorialUI : public CObj
{
public:
    CTutorialUI();
    CTutorialUI(const wstring& imgKey, const wstring& text, float x, float y);
    virtual ~CTutorialUI() {}

    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Set_Visible(bool bVisible);
    void Set_Text(const wstring& text);

private:
    wstring m_imgKey;
    wstring m_text;
    bool m_bVisible = true;

    // CObj을(를) 통해 상속됨
    void Late_Update() override;
    void Release() override;
};

