#pragma once
#include <Windows.h>

class CCameraMgr {
public:
    CCameraMgr();
    virtual ~CCameraMgr();
public:
    static CCameraMgr* Get_Instance();

    void Set_Target(int x, int y);
    void Update();

    POINT WorldToScreen(int x, int y) const;
    RECT Get_CameraRect() const;

    void Set_MapSize(int width, int height);
    void Set_Resolution(int width, int height);

private:
    POINT m_Pos;         // ī�޶� ���� ���
    POINT m_Target;      // ���� Ÿ�� ��ġ
    SIZE m_MapSize;
    SIZE m_Resolution;
};


