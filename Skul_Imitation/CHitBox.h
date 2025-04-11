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
    void Update_Rect();

    const RECT& Get_Rect() const;
    RECT& Get_Rect();
    POINT Get_Center() const;

    void Render(HDC hDC);

private:
    INFO m_tInfo;
    RECT m_tRect;
};
