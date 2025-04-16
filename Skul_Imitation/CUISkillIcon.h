#pragma once
#include "CObj.h"
class CUISkillIcon : public CObj
{
public:
    CUISkillIcon(float fX, float fY, const std::wstring& iconKey, const std::wstring& iconType);
    virtual ~CUISkillIcon();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    std::wstring Get_IconType() const;

    void Set_IconKey(const std::wstring& key);

private:
    std::wstring m_sIconKey;
    std::wstring m_sIconType;
};

