#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
    : m_fDeltaTime(0.f), m_fGlobalTimeScale(1.f), m_dwPrevTime(GetTickCount())
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Update()
{
    DWORD dwCurrTime = GetTickCount();
    m_fDeltaTime = (dwCurrTime - m_dwPrevTime) * 0.001f;
    m_dwPrevTime = dwCurrTime;
}
CTimeMgr* CTimeMgr::Get_Instance()
{
    if (!m_pInstance)
        m_pInstance = new CTimeMgr;
    return m_pInstance;
}

void CTimeMgr::Destroy_Instance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

float CTimeMgr::Get_DeltaTime() const { return m_fDeltaTime * m_fGlobalTimeScale; }
void CTimeMgr::Set_GlobalTimeScale(float scale) { m_fGlobalTimeScale = scale; }
float CTimeMgr::Get_GlobalTimeScale() const { return m_fGlobalTimeScale; }
