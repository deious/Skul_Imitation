#pragma once
#include "CObj.h"

//enum class EDirection { LEFT, RIGHT };

class CPlayer;

class CThrownHead : public CObj 
{
public:
    CThrownHead(CPlayer* pPlayer, float x, float y, float dir);
    virtual ~CThrownHead();

public:

    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Late_Update() override;
    void OnTileCollision(float landY) override;
    void Release() override {}


private:
    float m_fVelocityX;
    float m_fGravity;
    const float GRAVITY_ACCEL = 0.5f;
    bool m_bHitWall;
    DIRECTION m_dir;
};
