#pragma once
#include "Define.h"
#include "Istate.h"
#include "EPlayerState.h"

class CPlayer;

class CState : public IState<CPlayer>
{
public:
    virtual ~CState() = default;

    virtual void Enter(CPlayer* pPlayer) PURE;
    virtual void Update(CPlayer* pPlayer) PURE;
    virtual void Exit(CPlayer* pPlayer) PURE;

    virtual EPlayerState GetStateID() const PURE;
};
