#pragma once
#include "pch.h"
#include "Define.h"
#include "CObj.h"

class CUIMgr
{
public:
    static CUIMgr* Get_Instance();
    static void Destroy_Instance();

public:
    void Add_UI(CObj* pUI);
    void Update();
    void Late_Update();
    void Render(HDC hDC);
    void Release();

    template <typename T>
    T* Get_UI()
    {
        for (auto& pUI : m_vecUI)
        {
            T* casted = dynamic_cast<T*>(pUI);
            if (casted)
                return casted;
        }

        return nullptr;
    }

    const std::vector<CObj*>& Get_UIList() const;
    void ChangeIcon(std::wstring iconType, const std::wstring& newKey);
    CObj* Find_UI(const std::wstring& name);
    void Set_Mouse(CObj* pMouse);
    CObj* Get_Mouse() const;

private:
    CUIMgr() = default;
    ~CUIMgr();

private:
    static CUIMgr* m_pInstance;
    vector<CObj*> m_vecUI;
    CObj* m_pMouse = nullptr;
};

