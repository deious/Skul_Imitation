#pragma once
#include "CObj.h"
class CEffect : public CObj
{
public:
    CEffect();
    virtual ~CEffect();

public:
    void Initialize();
    void Initialize(const EffectInfo& tInfo, const Vec2& vFinalPos, CObj* pFollowTarget = nullptr);
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_EffectFrame(int iStart, int iEnd, int iSpeed);
    void Set_Priority(RENDERID r_id);

private:
    DWORD m_dwCreateTime;
    DWORD m_dwLastFrameTime;
    DWORD m_dwDuration;
    CObj* m_pFollowTarget = nullptr;
    EffectInfo m_tEffectInfo;
};

