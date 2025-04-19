#pragma once
#include "CObj.h"
class CGate : public CObj
{
public:
    CGate(const std::wstring& imageKey, INFO info, int stageNum);
    virtual ~CGate();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    void Set_Frame(int iStart, int iEnd, DWORD dwSpeed);

    void Set_Condition(std::function<bool()> condition);
    bool Is_Condition() const;

private:
    int m_iCurStageNum;
    std::function<bool()> m_Condition;
    std::wstring m_sFrameKey;
    bool m_bPlayerInRange = false;
};

