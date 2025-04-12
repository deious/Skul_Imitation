#pragma once
#include "pch.h"
#include "Define.h"

class CPlayer;

struct FrameData {
    int iStart;
    int iEnd;
    int iMotion;
    DWORD dwSpeed;
};

class CSkulHead {
public:
    virtual ~CSkulHead() {}

    virtual void UseSkillA(CPlayer* pPlayer) = 0;
    virtual void UseSkillS(CPlayer* pPlayer) = 0;
    virtual void UseSkillD(CPlayer* pPlayer) = 0;
    virtual const wchar_t* Get_IconKey() const = 0;
    virtual const wchar_t* Get_FrameKey(CPlayer* pPlayer) const = 0;
    virtual const wstring Get_SkulId() const = 0;
    //virtual unordered_map<ESkillType, FrameData> Get_SkillFrame() const = 0;
    virtual FRAME* Get_AllFrame() = 0;

    virtual void Update() {}

protected:
    //unordered_map<ESkillType, FrameData> m_mapSkillFrames;
    FRAME m_fFrame[SKUL_END];
    std::wstring sSkulName;
};