#pragma once
class CPlayer;

class CSkulHead {
public:
    virtual ~CSkulHead() {}

    virtual void UseSkillA(CPlayer* pPlayer) = 0;
    virtual void UseSkillS(CPlayer* pPlayer) = 0;
    virtual const wchar_t* GetIconKey() const = 0;

    virtual void Update() {}
};