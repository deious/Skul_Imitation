#include "pch.h"
#include "CEffect.h"
#include "CBmpMgr.h"

CEffect::CEffect() {}

CEffect::~CEffect()
{

}

void CEffect::Initialize()
{
	m_eRender = RENDER_EFFECT;
}

void CEffect::Initialize(const EffectInfo& tInfo, const Vec2& vFinalPos, CObj* pTarget)
{
	m_tInfo.fCX = tInfo.vSize.x;
	m_tInfo.fCY = tInfo.vSize.y;
	/*m_tInfo.fCX = vFinalPos.x;
	m_tInfo.fCY = vFinalPos.y;*/

	m_tEffectInfo = tInfo;
	m_pFollowTarget = pTarget;

	m_tFrame.iStart = tInfo.iStartFrame;
	Set_EffectFrame(tInfo.iStartFrame, tInfo.iEndFrame, tInfo.iFrameSpeed);

	m_eRender = RENDER_EFFECT;
	m_pFrameKey = tInfo.sFramekey;

	Set_Pos(vFinalPos.x, vFinalPos.y);
}

int CEffect::Update()
{
	DWORD dwCurTime = GetTickCount64();

	// 이펙트 수명 종료
	if (dwCurTime - m_dwCreateTime > m_dwDuration)
		return DEAD;

	// 애니메이션 프레임 갱신
	if (dwCurTime - m_dwLastFrameTime >= m_tFrame.dwFrameSpeed)
	{
		++m_tFrame.iMotion;
		m_dwLastFrameTime = dwCurTime;

		if (m_tFrame.iMotion > m_tFrame.iEnd)
			m_tFrame.iMotion = m_tFrame.iEnd; // 멈추게 하거나 반복할 수도 있음
	}

	if (m_pFollowTarget)
	{
		Vec2 followPos = {
			m_pFollowTarget->Get_Info()->fX + m_tEffectInfo.vOffset.x,
			m_pFollowTarget->Get_Info()->fY + m_tEffectInfo.vOffset.y
		};
		Set_Pos(followPos.x, followPos.y);
	}

	return 0;
}

void CEffect::Late_Update()
{
}

void CEffect::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	POINT screenPos = CCameraMgr::Get_Instance()->WorldToScreen((int)m_tInfo.fX, (int)m_tInfo.fY);

	int drawX = screenPos.x - (int)(m_tInfo.fCX * 0.5f);
	int drawY = screenPos.y - (int)(m_tInfo.fCY * 0.5f);

	GdiTransparentBlt(hDC,
		drawX,
		drawY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iMotion * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CEffect::Set_EffectFrame(int start, int end, int speed)
{
	m_tFrame.iStart = start;
	m_tFrame.iMotion = start;
	m_tFrame.iEnd = end;
	m_tFrame.dwFrameSpeed = speed;
	m_dwCreateTime = GetTickCount64();
	m_dwLastFrameTime = GetTickCount64();
	m_dwDuration = (end - start + 1) * speed;
}

void CEffect::Release()
{
}
