#pragma once
#include "CObj.h"
class CEffect : public CObj
{
public:
    CEffect();
    virtual ~CEffect();

public:
    void Initialize();
    void Initialize(const EffectInfo& tInfo);
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_EffectFrame(int iStart, int iEnd, int iSpeed);

private:
    DWORD m_dwCreateTime;
    DWORD m_dwLastFrameTime;
    DWORD m_dwDuration;
};

