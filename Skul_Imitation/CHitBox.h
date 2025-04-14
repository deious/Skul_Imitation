#pragma once
#include "Define.h"
#include "CCameraMgr.h"

class CHitBox
{
public:
    CHitBox();
    CHitBox(float x, float y, float cx, float cy);

    void Set_Pos(float x, float y);
    void Set_Size(float cx, float cy);
    void Set_LastHitFrame(DWORD frame);
    void Set_MaxHits(int iMaxHits);
    void Set_Offset(float x, float y);
    void Reset_HitCount();
    void Update_Rect();

    const RECT& Get_Rect() const;
    RECT& Get_Rect();
    POINT Get_Center() const;
    DWORD Get_LastHitFrame() const;
    int Get_MaxHit() const;
    bool Can_Hit() const;
    void Add_Hit();

    void Render(HDC hDC);

private:
    int m_iHitCount = 0;
    int m_iMaxHits = 1;

    INFO m_tInfo;
    RECT m_tRect;
    DWORD m_dwLastHitFrame = 0;

    Vec2 m_vOffset = { 0.f, 0.f };
};
