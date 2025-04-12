#include "pch.h"
#include "CThrownHead.h"
#include "CBmpMgr.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CTileMgr.h"
#include "CLineMgr.h"
#include "CPlayer.h"

CThrownHead::CThrownHead(CPlayer* pPlayer, float x, float y, float dir)
    : m_fVelocityX(5.f * dir), m_fGravity(0.f), m_bHitWall(false)
{
    float offset = (pPlayer->Get_Direction() == DIR_RIGHT) ? +30.f : -30.f;
    m_tInfo = { x + offset, y, 15.f, 13.f };
    m_dir = pPlayer->Get_Direction();
}

CThrownHead::~CThrownHead()
{
}

void CThrownHead::Initialize() 
{
    m_eRender = RENDER_GAMEOBJECT;
    m_tInfo = { m_tInfo.fX, m_tInfo.fY, 15.f, 13.f };
    m_fSpeed = 6.f;
    m_bDead = false;

    /*CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Right.bmp", L"Skul_Head_Right");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Skul/Skul_Head_Left.bmp", L"Skul_Head_Left");*/

    if (m_dir == DIR_LEFT)
    {
        m_pFrameKey = L"Skul_Head_Left";
    }
    else
    {
        m_pFrameKey = L"Skul_Head_Right";
    }

    m_tFrame.dwTime = GetTickCount64();
    m_tFrame.dwFrameSpeed = 120;

    // HitBox ���� �͵� ���⿡ ����
    m_pHitBox = new CHitBox(m_tInfo.fX, m_tInfo.fY, 20.f, 20.f);
}

int CThrownHead::Update() {
    if (m_bDead)
        return DEAD;

    if (!m_bHitWall) 
    {
        m_tInfo.fX += m_fVelocityX;
    }
    else 
    {
        m_fGravity += GRAVITY_ACCEL;
        m_tInfo.fY += m_fGravity;
    }

    Update_Rect();
    if (m_pHitBox)
        m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);

    return 0;
}

void CThrownHead::Render(HDC hDC) {
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey); // �Ǵ� ���� ���� Left/Right

    POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

    int drawX = screenPos.x - (int)(m_tInfo.fCX * 0.5f);
    int drawY = screenPos.y - (int)(m_tInfo.fCY * 0.5f);

    GdiTransparentBlt(hDC,
        drawX,
        drawY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        0, 0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)
    );

    if (CKeyMgr::Get_Instance()->Get_ShowAll())
    {
        POINT screen = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

        RECT drawRc;
        drawRc.left = (LONG)(screen.x - m_tInfo.fCX * 0.5f);
        drawRc.top = (LONG)(screen.y - m_tInfo.fCY * 0.5f);
        drawRc.right = (LONG)(screen.x + m_tInfo.fCX * 0.5f);
        drawRc.bottom = (LONG)(screen.y + m_tInfo.fCY * 0.5f);

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        FrameRect(hDC, &drawRc, hBrush);
        DeleteObject(hBrush);
    }
}

void CThrownHead::Late_Update()
{
    //MessageBox(g_hWnd, L"����Ʈ������Ʈ", _T("Fail"), MB_OK);
    /*CCollisionMgr::PlayerToTile(this, CTileMgr::Get_Instance()->Get_Tree());

    RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
    RECT rc;
    if (!IntersectRect(&rc, &camRect, &m_tRect))
    {
        if (!m_bHitWall)
        {
            m_bHitWall = true;
            m_fGravity = -5.f;
        }
    }

    if (m_bHitWall)
    {
        m_fGravity += GRAVITY_ACCEL;
        m_tInfo.fY += m_fGravity;
    }

    if (m_pHitBox)
        m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);*/

    RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
    //RECT rcIntersection;
    //if (!IntersectRect(&rcIntersection, &camRect, &m_tRect) && !m_bHitWall)
    //{
    //    m_bHitWall = true;
    //    m_fGravity = -5.f; // ��¦ ����
    //}

    // �� �Ǵ� �ٴ� �浹 �˻�
    if (!m_bHitWall)
    {
        //m_bHitWall = true;
        CCollisionMgr::PlayerToTile(this, CTileMgr::Get_Instance()->Get_Tree());
    }
    else
    {
        m_fGravity += GRAVITY_ACCEL;
        m_tInfo.fY += m_fGravity;
        m_bHitWall = true;

        // ���� ������ �߷� ���ߵ��� ó�� (�� �̻� ƨ���� �ʰ�)
        float groundY = 0.f;
        if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &groundY) &&
            m_tInfo.fY >= groundY)
        {
            m_tInfo.fY = groundY;
            m_fGravity = 0.f;
        }
    }

    // ��Ʈ�ڽ� ��ġ ����
    /*if (m_pHitBox)
        m_pHitBox->Set_Pos(m_tInfo.fX, m_tInfo.fY);*/


}

void CThrownHead::OnTileCollision(float landY)
{
    m_tInfo.fY = landY;
    m_bHitWall = true;
    m_fGravity = -5.f;
}