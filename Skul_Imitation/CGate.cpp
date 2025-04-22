#include "pch.h"
#include "CGate.h"
#include "CKeyMgr.h"
#include "CObjMgr.h"
#include "CSceneMgr.h"
#include "CBmpMgr.h"

CGate::CGate(const std::wstring& frameKey, INFO info, int stage)
{
    m_tInfo.fCX = info.fCX;
    m_tInfo.fCY = info.fCY;
    m_tInfo.fX = info.fX;
    m_tInfo.fY = info.fY;
    m_sFrameKey = frameKey;
    m_iCurStageNum = stage;
    m_eRender = RENDER_GAMEOBJECT;
}

CGate::~CGate()
{
}

void CGate::Initialize()
{
}

int CGate::Update()
{
    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    if (!pPlayer)
        return 0;

    float dx = pPlayer->Get_Info()->fX - m_tInfo.fX;
    float dy = pPlayer->Get_Info()->fY - m_tInfo.fY;
    float distSq = dx * dx + dy * dy;
    m_bPlayerInRange = distSq < 100.f * 100.f;

    if (m_bPlayerInRange && CKeyMgr::Get_Instance()->Key_Down('F'))
    {
        if (CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).empty() && CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS).empty())
        {
            CSceneMgr::Get_Instance()->RequestSceneChange(
                static_cast<CSceneMgr::SCENEID>(m_iCurStageNum + 1));
        }
        /*if (m_Condition )
        {
            CSceneMgr::Get_Instance()->Scene_Change(static_cast<CSceneMgr::SCENEID>(m_iCurStageNum + 1));
        }
        else
        {
            OutputDebugString(L"[Gate] 조건을 만족하지 않아 이동 불가\n");
        }*/
    }

    Move_Frame();
    return 0;
}

void CGate::Late_Update()
{
    __super::Update_Rect();
}

void CGate::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_sFrameKey.c_str());
    if (!hMemDC) return;

    POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);
    GdiTransparentBlt(hDC,
        screen.x - (int)(m_tInfo.fCX * 0.5f),
        screen.y - (int)(m_tInfo.fCY * 0.5f),
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        m_tFrame.iStart * (int)m_tInfo.fCX,
        0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));

    /*if (m_bPlayerInRange)
    {
        RECT rcText = {
            screen.x - 40,
            screen.y - 80,
            screen.x + 40,
            screen.y - 60
        };
        SetBkMode(hDC, TRANSPARENT);
        SetTextColor(hDC, RGB(255, 255, 255));
        DrawText(hDC, L"F: 다음 스테이지로", -1, &rcText, DT_CENTER | DT_SINGLELINE);
    }*/
}

void CGate::Set_Frame(int iStart, int iEnd, DWORD dwSpeed)
{
    m_tFrame.iStart = iStart;
    m_tFrame.iEnd = iEnd;
    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = dwSpeed;
}

void CGate::Release()
{

}

void CGate::Set_Condition(std::function<bool()> condition)
{
    m_Condition = condition;
}

bool CGate::Is_Condition() const
{
    if (m_Condition)
        return m_Condition();
    return false;
}
