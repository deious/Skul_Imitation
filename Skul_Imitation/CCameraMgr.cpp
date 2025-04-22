#include "pch.h"
#include "CCameraMgr.h"
#include "Define.h"
#include "CTimeMgr.h"

CCameraMgr::CCameraMgr()
{
    m_Pos = { 0, 0 };
    m_Target = { 0, 0 };
    m_MapSize = { 8000, 6000 };
    m_Resolution = { 800, 600 };
}

CCameraMgr::~CCameraMgr()
{
}

CCameraMgr* CCameraMgr::Get_Instance()
{
    static CCameraMgr instance;
    return &instance;
}

void CCameraMgr::Set_Target(int x, int y) 
{
    m_Target = { x, y };
}

void CCameraMgr::Update() 
{
    m_Pos.x = m_Target.x - m_Resolution.cx * 0.5f;
    m_Pos.y = m_Target.y - m_Resolution.cy * 0.5f;

    if (m_Pos.x < 0)
        m_Pos.x = 0;
    else if (m_Pos.x > m_MapSize.cx - m_Resolution.cx)
        m_Pos.x = m_MapSize.cx - m_Resolution.cx;

    if (m_Pos.y < 0)
        m_Pos.y = 0;
    else if (m_Pos.y > m_MapSize.cy - m_Resolution.cy)
        m_Pos.y = m_MapSize.cy - m_Resolution.cy;

    if (m_fShakeTimer < m_fShakeDuration)
    {
        m_fShakeTimer += DELTA_TIME;

        // ���� ��鸲 ������
        int offsetX = (rand() % (int)(m_fShakeIntensity * 2)) - (int)m_fShakeIntensity;
        int offsetY = (rand() % (int)(m_fShakeIntensity * 2)) - (int)m_fShakeIntensity;

        m_ptShakeOffset.x = offsetX;
        m_ptShakeOffset.y = offsetY;
    }
    else
    {
        m_ptShakeOffset.x = 0;
        m_ptShakeOffset.y = 0;
    }
}

POINT CCameraMgr::WorldToScreen(int x, int y) const 
{
    /*return { x - m_Pos.x, y - m_Pos.y };*/
    return {
        x - m_Pos.x + m_ptShakeOffset.x,
        y - m_Pos.y + m_ptShakeOffset.y
    };
}

RECT CCameraMgr::Get_CameraRect() const 
{
    return 
    {
        m_Pos.x,
        m_Pos.y,
        m_Pos.x + m_Resolution.cx,
        m_Pos.y + m_Resolution.cy
    };
}

void CCameraMgr::Set_MapSize(int width, int height) 
{
    m_MapSize = { width, height };
}

void CCameraMgr::Set_Resolution(int width, int height) 
{
    m_Resolution = { width, height };
}

void CCameraMgr::StartShake(float duration, float intensity)
{
    m_fShakeDuration = duration;
    m_fShakeTimer = 0.f;
    m_fShakeIntensity = intensity;
}

POINT CCameraMgr::Get_CameraPos() const
{
    return m_Pos;
}

RECT CCameraMgr::WorldToScreenRect(const RECT& worldRect)
{
    POINT camOffset = CCameraMgr::Get_Instance()->Get_CameraPos();

    RECT screenRect;
    screenRect.left = worldRect.left - camOffset.x;
    screenRect.top = worldRect.top - camOffset.y;
    screenRect.right = worldRect.right - camOffset.x;
    screenRect.bottom = worldRect.bottom - camOffset.y;

    return screenRect;
}

RECT CCameraMgr::SetAndGet_ExtendedCameraRect(int marginX, int marginY) const
{
    return
    {
        m_Pos.x - marginX,
        m_Pos.y - marginY,
        m_Pos.x + m_Resolution.cx + marginX,
        m_Pos.y + m_Resolution.cy + marginY
    };
}