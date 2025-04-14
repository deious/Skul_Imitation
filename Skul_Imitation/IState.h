#pragma once
#include "EBossStateType.h"

template<typename T>
class IState
{
public:
	virtual ~IState() = default;
	virtual void Enter(T* obj) = 0;
	virtual void Update(T* obj) = 0;
	virtual void Exit(T* obj) = 0;
	virtual EBossStateType GetType() {
		return EBossStateType();
	}
};
