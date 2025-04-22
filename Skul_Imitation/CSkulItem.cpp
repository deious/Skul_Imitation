#include "pch.h"
#include "CSkulItem.h"

CSkulItem::CSkulItem(const wstring& _key) : m_sFrameKey(_key) {}

const TCHAR* CSkulItem::Get_FrameKey() const { return m_sFrameKey.c_str(); }
