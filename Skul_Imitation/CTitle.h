#pragma once
#include "CScene.h"

class CTitle : public CScene
{
public:
    CTitle();
    virtual ~CTitle();

public:
    void        Initialize() override;
    int         Update() override;
    void        Late_Update() override;
    void        Render(HDC hDC) override;
    void        Release() override;

private:
    HWND        m_hVideo;

};

