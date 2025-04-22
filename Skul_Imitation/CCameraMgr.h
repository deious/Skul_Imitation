#pragma once
#include <Windows.h>

class CCameraMgr 
{
public:
    CCameraMgr();
    virtual ~CCameraMgr();
public:
    static CCameraMgr*  Get_Instance();

    void                Set_Target(int x, int y);
    void                Update();

    POINT               WorldToScreen(int x, int y) const;
    RECT                Get_CameraRect() const;

    void                Set_MapSize(int width, int height);
    void                Set_Resolution(int width, int height);
    void                StartShake(float duration, float intensity);

    POINT               Get_CameraPos() const;
    RECT                WorldToScreenRect(const RECT& worldRect);

    RECT                SetAndGet_ExtendedCameraRect(int marginX, int marginY) const;

private:
    POINT               m_Pos;
    POINT               m_Target;
    SIZE                m_MapSize;
    SIZE                m_Resolution;

    float               m_fShakeDuration = 0.f;
    float               m_fShakeTimer = 0.f;
    float               m_fShakeIntensity = 0.f;
    POINT               m_ptShakeOffset = { 0, 0 };
};
