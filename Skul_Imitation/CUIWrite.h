#pragma once
#include "CObj.h"
class CUIWrite : public CObj
{
public:
    CUIWrite(float x, float y, float width, float height, const std::wstring& text, int fontSize = 16);
    virtual ~CUIWrite();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Text(const std::wstring& text);

private:
    std::wstring m_sText;
    int m_iFontSize;
};

