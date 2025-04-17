#include "pch.h"
#include "CEffectMgr.h"
#include "CObjMgr.h"
#include "CObj.h"
#include "CEffect.h"
#include "CSoundMgr.h"

CEffectMgr* CEffectMgr::Get_Instance() {
    static CEffectMgr instance;
    return &instance;
}

void CEffectMgr::Add_Effect(const EffectInfo& tInfo, const Vec2& _vFinalPos, CObj* pTarget)
{
    Vec2 vFinalPos = { _vFinalPos.x + tInfo.vOffset.x, _vFinalPos.y + tInfo.vOffset.y };

    wchar_t buf[128];
    swprintf_s(buf, L"[EffectMgr] Creating Effect at (%.1f, %.1f)\n", vFinalPos.x, vFinalPos.y);
    OutputDebugString(buf);

    CObj* pEffect = Create_Effect(tInfo, vFinalPos, pTarget);

    if (pEffect)
    {
        OutputDebugString(L"[EffectMgr] Effect created. Adding to ObjMgr.\n");
        CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, pEffect);
    }
    else
    {
        OutputDebugString(L"[EffectMgr] Failed to create Effect!\n");
        return;
    }
}

void CEffectMgr::Update()
{
}

void CEffectMgr::Render(HDC hDC)
{
}

void CEffectMgr::Release()
{
}

CObj* CEffectMgr::Create_Effect(const EffectInfo& tInfo, const Vec2& vFinalPos, CObj* pTarget)
{
    CObj* pEffect = new CEffect();

    dynamic_cast<CEffect*>(pEffect)->Initialize(tInfo, vFinalPos, pTarget);           // 모든 이펙트 정보 설정
    //pEffect->Set_Pos(vFinalPos.x, vFinalPos.y);          // 위치만 별도로 지정

    if (!pTarget)
        pEffect->Set_Pos(vFinalPos.x, vFinalPos.y);

    /*if (tInfo.bPlaySound)
        CSoundMgr::Get_Instance()->PlaySound(tInfo.eSound, tInfo.eSound);*/

    return pEffect;
}

