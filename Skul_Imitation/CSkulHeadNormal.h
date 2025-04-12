#pragma once
#include "CSkulHead.h"
#include "CPlayer.h"

class CThrownHead;

class CSkulHeadNormal : public CSkulHead
{
public:
    CSkulHeadNormal();
    virtual ~CSkulHeadNormal();

public:
    void UseSkillA(CPlayer* pPlayer) override;
    void UseSkillS(CPlayer* pPlayer) override;
    void UseSkillD(CPlayer* pPlayer) override;
    void Update() override;

    const wchar_t* Get_IconKey() const override;
    const wchar_t* Get_FrameKey(CPlayer* pPlayer) const override;
    const wstring Get_SkulId() const override;
    FRAME* Get_AllFrame() override;
    //unordered_map<ESkillType, FrameData> Get_SkillFrame() const override;

private:
    CThrownHead* m_pThrownHead = nullptr;
    bool m_bHeadThrown = false;
};

