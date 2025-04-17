#pragma once
#include "Define.h"

class CObj;

class CEffectMgr
{
public:
    static CEffectMgr* Get_Instance();

    void Add_Effect(const EffectInfo& tInfo, const Vec2& vFinalPos, CObj* pTarget = nullptr);

    void Update();
    void Render(HDC hDC);
    void Release();

private:
    CObj* Create_Effect(const EffectInfo& tInfo, const Vec2& vFinalPos, CObj* pTarget);
};

