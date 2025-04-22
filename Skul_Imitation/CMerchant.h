#pragma once
#include "CObj.h"
class CMerchant :
    public CObj
{
public:
    CMerchant();
    virtual ~CMerchant();

public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Set_Frame(int iStart, int iEnd, DWORD dwSpeed);

private:
    std::wstring m_sFrameKey;
};

