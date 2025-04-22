#pragma once

class CTimeMgr
{
public:
    CTimeMgr();
    ~CTimeMgr();

public:
    static CTimeMgr* Get_Instance();
    static void Destroy_Instance();

public:
    void Update();

    float Get_DeltaTime() const;
    void Set_GlobalTimeScale(float scale);
    float Get_GlobalTimeScale() const;

private:
    static CTimeMgr* m_pInstance;

    float m_fDeltaTime;
    float m_fGlobalTimeScale;
    DWORD m_dwPrevTime;
};