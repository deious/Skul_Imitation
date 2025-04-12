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
    void Update() override;

    const wchar_t* GetIconKey() const override;

private:
    CThrownHead* m_pThrownHead = nullptr;
    bool m_bHeadThrown = false;
};

