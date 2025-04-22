#pragma once
#include "CScene.h"
class CSceneEnding :
    public CScene
{
public:
    // CScene��(��) ���� ��ӵ�
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    std::vector<std::wstring> m_vecCredits;
    float m_fScrollY = 0.f;
    DWORD m_dwStartTime = 0;
};

