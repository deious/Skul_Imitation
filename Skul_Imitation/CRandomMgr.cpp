#include "pch.h"
#include "CRandomMgr.h"

CRandomMgr* CRandomMgr::m_pInstance = nullptr;

CRandomMgr* CRandomMgr::Get_Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CRandomMgr;
	}

	return m_pInstance;
}

std::mt19937& CRandomMgr::GetGenerator()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return gen;
}

int CRandomMgr::GetRandom(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(GetGenerator());
}
