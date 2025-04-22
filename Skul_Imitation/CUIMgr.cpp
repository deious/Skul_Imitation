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

void CUIMgr::Set_Mouse(CObj* pMouse) { m_pMouse = pMouse; }

CObj* CUIMgr::Get_Mouse() const { return m_pMouse; }

const std::vector<CObj*>& CUIMgr::Get_UIList() const { return m_vecUI; }

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

CObj* CUIMgr::Find_UI(const std::wstring& name)
{
    for (auto& pUI : m_vecUI)
    {
        if (pUI->Get_Tag() == name)
            return pUI;
    }

    return nullptr;
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

    if (m_pMouse)
    {
        //OutputDebugString(L"[CUIMgr] 마우스 Update 호출됨\n");
        m_pMouse->Update();  // 마우스도 직접 호출
    }
}

void CUIMgr::Late_Update()
{
    for (auto pUI : m_vecUI)
        pUI->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
    /*for (auto pUI : m_vecUI)
        pUI->Render(hDC);*/

    /*for (auto pUI : m_vecUI)
    {
        if (pUI != m_pMouse)
            pUI->Render(hDC);
    }

    if (m_pMouse)
        m_pMouse->Render(hDC);*/

    for (auto pUI : m_vecUI)
    {
        if (pUI->Get_Tag() != L"MOUSE")
            pUI->Render(hDC);
    }

    for (auto pUI : m_vecUI)
    {
        if (pUI->Get_Tag() == L"MOUSE")
        {
            OutputDebugString(L"[CUIMgr] MOUSE Update 호출됨\n");
            pUI->Render(hDC);
        }
    }
}

void CUIMgr::Release()
{
    for (auto& pUI : m_vecUI)
        Safe_Delete(pUI);
    m_vecUI.clear();
}
