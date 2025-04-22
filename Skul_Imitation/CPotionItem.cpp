#include "pch.h"
#include "CPotionItem.h"
#include "CObjMgr.h"

CPotionItem::CPotionItem(const std::wstring& key) : m_sFrameKey(key) {}

CPotionItem::~CPotionItem() {}

const TCHAR* CPotionItem::Get_FrameKey() const
{
	return m_sFrameKey.c_str();
}

int CPotionItem::Get_HealAmount()
{
	return m_iHealAmount;
}
