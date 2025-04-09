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

private:
    CUIMgr() = default;
    ~CUIMgr();

private:
    static CUIMgr* m_pInstance;
    vector<CObj*> m_vecUI;
};