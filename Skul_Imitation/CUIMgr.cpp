#include "pch.h"
#include "CUIMgr.h"
#include "CUISkillIcon.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr* CUIMgr::Get_Instance()
{
    if (!m_pInstance)
        m_pInstance = new CUIMgr;
    return m_pInstance;
}

void CUIMgr::Destroy_Instance()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

void CUIMgr::ChangeIcon(std::wstring iconType, const std::wstring& newKey)
{
    for (auto& pUI : m_vecUI)
    {
        CUISkillIcon* pIcon = dynamic_cast<CUISkillIcon*>(pUI);
        if (!pIcon) continue;

        if (pIcon->Get_IconType() == iconType)
        {
            pIcon->Set_IconKey(newKey);
            break;
        }
    }
}

CUIMgr::~CUIMgr()
{
    Release();
}

void CUIMgr::Add_UI(CObj* pUI)
{
    if (pUI)
        m_vecUI.push_back(pUI);
}

void CUIMgr::Update()
{
    for (auto pUI : m_vecUI)
        pUI->Update();
}

void CUIMgr::Late_Update()
{
    for (auto pUI : m_vecUI)
        pUI->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
    for (auto pUI : m_vecUI)
        pUI->Render(hDC);
}

void CUIMgr::Release()
{
    for (auto& pUI : m_vecUI)
        Safe_Delete(pUI);
    m_vecUI.clear();
}
