#include "pch.h"
#include "CCameraMgr.h"

CCameraMgr::CCameraMgr()
{
    m_Pos = { 0, 0 };
    m_Target = { 0, 0 };
    m_MapSize = { 8000, 6000 };        // 기본 맵 크기
    m_Resolution = { 800, 600 };       // 기본 해상도
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
    // 부드러운 이동 (Lerp)
    //float factor = 0.1f;
    //m_Pos.x = int(m_Pos.x + (m_Target.x - m_Pos.x - m_Resolution.cx / 2) * factor);
    //m_Pos.y = int(m_Pos.y + (m_Target.y - m_Pos.y - m_Resolution.cy / 2) * factor);

    m_Pos.x = m_Target.x - m_Resolution.cx * 0.5f;
    m_Pos.y = m_Target.y - m_Resolution.cy * 0.5f;

    // 경계 제한
    if (m_Pos.x < 0)
        m_Pos.x = 0;
    else if (m_Pos.x > m_MapSize.cx - m_Resolution.cx)
        m_Pos.x = m_MapSize.cx - m_Resolution.cx;

    if (m_Pos.y < 0)
        m_Pos.y = 0;
    else if (m_Pos.y > m_MapSize.cy - m_Resolution.cy)
        m_Pos.y = m_MapSize.cy - m_Resolution.cy;
}

POINT CCameraMgr::WorldToScreen(int x, int y) const 
{
    return { x - m_Pos.x, y - m_Pos.y };
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

POINT CCameraMgr::Get_CameraPos() const
{
    return m_Pos;
}