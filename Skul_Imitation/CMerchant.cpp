#include "pch.h"
#include "CMerchant.h"
#include "CBmpMgr.h"

CMerchant::CMerchant()
{
    m_eRender = RENDER_PRIORITY;
    m_tInfo.fCX = 300.f;
    m_tInfo.fCY = 200.f;
    m_sFrameKey = L"TwinHead";
}

CMerchant::~CMerchant()
{
}

void CMerchant::Initialize()
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 200.f;
    m_eRender = RENDER_PRIORITY;
    m_sFrameKey = L"TwinHead";
}

int CMerchant::Update()
{
    //OutputDebugString(L"[CMerchant] Update 호출됨\n");
    Move_Frame();
	return 0;
}

void CMerchant::Late_Update()
{
    __super::Update_Rect();
}

void CMerchant::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_sFrameKey.c_str());
    if (!hMemDC)
    {
        OutputDebugString(L"[CMerchant] 이미지 못 찾음\n");
        return;
    }
    if (!hMemDC) return;

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)(m_tInfo.fY));
    GdiTransparentBlt(
        hDC,
        screen.x - (int)(m_tInfo.fCX * 0.5f),
        screen.y - (int)(m_tInfo.fCY * 0.5f),
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        hMemDC,
        m_tFrame.iStart * (int)m_tInfo.fCX, 0,
        (int)m_tInfo.fCX, (int)m_tInfo.fCY,
        RGB(255, 0, 255));
}

void CMerchant::Release()
{
}

void CMerchant::Set_Frame(int iStart, int iEnd, DWORD dwSpeed)
{
    m_tFrame.iStart = iStart;
    m_tFrame.iEnd = iEnd;
    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = dwSpeed;
}