#pragma once
#include "Define.h"

class CObj;

class CEffectMgr
{
public:
    static CEffectMgr* Get_Instance();

    void Add_Effect(const EffectInfo& tInfo, const Vec2& vFinalPos);

    void Update();
    void Render(HDC hDC);
    void Release();

private:
    // 생성은 내부 팩토리로 분리
    CObj* Create_Effect(const EffectInfo& tInfo, const Vec2& vFinalPos);
};

