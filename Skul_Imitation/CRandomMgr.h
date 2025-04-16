#pragma once

class CRandomMgr
{
public:
	static CRandomMgr* Get_Instance();

	static std::mt19937& GetGenerator();
	static int GetRandom(int min, int max);

private:
	static CRandomMgr* m_pInstance;
};