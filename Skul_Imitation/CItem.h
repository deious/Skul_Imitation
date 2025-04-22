#pragma once
#include "Define.h"

class CItem
{
public:
    CItem();
    virtual ~CItem();

public:
    virtual const TCHAR* Get_FrameKey() const PURE;
};
