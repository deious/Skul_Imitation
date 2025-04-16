#include "pch.h"
#include "CSoundMgr.h"


//CSoundMgr* CSoundMgr::m_pInstance = nullptr;
//CSoundMgr::CSoundMgr()
//{
//	m_pSystem = nullptr;
//}
//
//
//CSoundMgr::~CSoundMgr()
//{
//	Release();
//}
//
//void CSoundMgr::Initialize()
//{
//	// ���带 ����ϴ� ��ǥ��ü�� �����ϴ� �Լ�
//	FMOD_System_Create(&m_pSystem);
//
//	// 1. �ý��� ������, 2. ����� ����ä�� �� , �ʱ�ȭ ���) 
//	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
//
//	LoadSoundFile();
//}
//void CSoundMgr::Release()
//{
//	for (auto& Mypair : m_mapSound)
//	{
//		delete[] Mypair.first;
//		FMOD_Sound_Release(Mypair.second);
//	}
//	m_mapSound.clear();
//
//	FMOD_System_Release(m_pSystem);
//	FMOD_System_Close(m_pSystem);
//}
//
//void CSoundMgr::PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume)
//{
//	map<TCHAR*, FMOD_SOUND*>::iterator iter;
//
//	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
//	iter = find_if(m_mapSound.begin(), m_mapSound.end(),
//		[&](auto& iter)->bool
//		{
//			return !lstrcmp(pSoundKey, iter.first);
//		});
//
//	if (iter == m_mapSound.end())
//		return;
//
//	FMOD_BOOL bPlay = FALSE;
//
//	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
//	{
//		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
//	}
//
//	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);
//
//	FMOD_System_Update(m_pSystem);
//}
//
//void CSoundMgr::PlayBGM(const TCHAR* pSoundKey, float fVolume)
//{
//	map<TCHAR*, FMOD_SOUND*>::iterator iter;
//
//	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
//	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
//		{
//			return !lstrcmp(pSoundKey, iter.first);
//		});
//
//	if (iter == m_mapSound.end())
//		return;
//
//	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[SOUND_BGM]);
//	FMOD_Channel_SetMode(m_pChannelArr[SOUND_BGM], FMOD_LOOP_NORMAL);
//	FMOD_Channel_SetVolume(m_pChannelArr[SOUND_BGM], fVolume);
//	FMOD_System_Update(m_pSystem);
//}
//
//void CSoundMgr::StopSound(CHANNELID eID)
//{
//	FMOD_Channel_Stop(m_pChannelArr[eID]);
//}
//
//void CSoundMgr::StopAll()
//{
//	for (int i = 0; i < SOUND_END; ++i)
//		FMOD_Channel_Stop(m_pChannelArr[i]);
//}
//
//void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
//{
//	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);
//
//	FMOD_System_Update(m_pSystem);
//}
//
//void CSoundMgr::LoadSoundFile()
//{
//	// _finddata_t : <io.h>���� �����ϸ� ���� ������ �����ϴ� ����ü
//	_finddata_t fd;
//
//	// _findfirst : <io.h>���� �����ϸ� ����ڰ� ������ ��� ������ ���� ù ��° ������ ã�� �Լ�
//	long handle = _findfirst("./Sound/*.*", &fd);
//
//	if (handle == -1)
//		return;
//
//	int iResult = 0;
//
//	char szCurPath[128] = "./Sound/";	 // ��� ���
//	char szFullPath[128] = "";
//
//	while (iResult != -1)
//	{
//		strcpy_s(szFullPath, szCurPath);
//
//		// "../Sound/" + "Success.wav"
//		strcat_s(szFullPath, fd.name);
//		// "../Sound/Success.wav"
//
//		FMOD_SOUND* pSound = nullptr;
//
//		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);
//
//		if (eRes == FMOD_OK)
//		{
//			int iLength = strlen(fd.name) + 1;
//
//			TCHAR* pSoundKey = new TCHAR[iLength];
//			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
//
//			// �ƽ�Ű �ڵ� ���ڿ��� �����ڵ� ���ڿ��� ��ȯ�����ִ� �Լ�
//			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);
//
//			m_mapSound.emplace(pSoundKey, pSound);
//		}
//		//_findnext : <io.h>���� �����ϸ� ���� ��ġ�� ������ ã�� �Լ�, ���̻� ���ٸ� -1�� ����
//		iResult = _findnext(handle, &fd);
//	}
//
//	FMOD_System_Update(m_pSystem);
//
//	_findclose(handle);
//}

CSoundMgr* CSoundMgr::m_pInstance = nullptr;

CSoundMgr::CSoundMgr() {}
CSoundMgr::~CSoundMgr() { Release(); }

void CSoundMgr::Initialize()
{
    FMOD_System_Create(&m_pSystem);
    FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, nullptr);
    LoadSoundFile();
}

void CSoundMgr::Release()
{
    for (auto& pair : m_mapSound)
        FMOD_Sound_Release(pair.second);

    m_mapSound.clear();
    FMOD_System_Close(m_pSystem);
    FMOD_System_Release(m_pSystem);
}

void CSoundMgr::LoadSoundFile()
{
    _finddata_t fd;
    long handle = _findfirst("./Sound/*.*", &fd);
    if (handle == -1) return;

    int result = 0;
    char fullPath[128] = "";

    while (result != -1)
    {
        std::string path = "./Sound/" + std::string(fd.name);
        FMOD_SOUND* pSound = nullptr;

        FMOD_RESULT res = FMOD_System_CreateSound(m_pSystem, path.c_str(), FMOD_DEFAULT | FMOD_LOOP_OFF, 0, &pSound);
        if (res == FMOD_OK)
        {
            std::wstring key(fd.name, fd.name + strlen(fd.name));
            m_mapSound.emplace(key, pSound);
        }

        result = _findnext(handle, &fd);
    }

    _findclose(handle);
    FMOD_System_Update(m_pSystem);
}

void CSoundMgr::Play(const std::wstring& key, int loopCount, float volume)
{
    auto iter = m_mapSound.find(key);
    if (iter == m_mapSound.end()) return;

    FMOD_SOUND* pSound = iter->second;

    if (loopCount != 0)
    {
        FMOD_Sound_SetMode(pSound, FMOD_LOOP_NORMAL);
        FMOD_Sound_SetLoopCount(pSound, loopCount < 0 ? -1 : loopCount);
    }
    else
    {
        FMOD_Sound_SetMode(pSound, FMOD_LOOP_OFF);
    }

    FMOD_CHANNEL* pChannel = nullptr;
    FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, pSound, FALSE, &pChannel);
    FMOD_Channel_SetVolume(pChannel, volume);
    FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(const std::wstring& key, float volume)
{
    auto iter = m_mapSound.find(key);
    if (iter == m_mapSound.end()) return;

    FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pBGMChannel);
    FMOD_Channel_SetMode(m_pBGMChannel, FMOD_LOOP_NORMAL);
    FMOD_Channel_SetVolume(m_pBGMChannel, volume);
    FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopBGM()
{
    if (m_pBGMChannel)
        FMOD_Channel_Stop(m_pBGMChannel);
}

void CSoundMgr::SetBGMVolume(float volume)
{
    if (m_pBGMChannel)
        FMOD_Channel_SetVolume(m_pBGMChannel, volume);
    FMOD_System_Update(m_pSystem);
}
