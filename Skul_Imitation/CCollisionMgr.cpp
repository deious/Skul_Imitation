#include "pch.h"
#include "Define.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CPlayer.h"
#include "CAttackCollider.h"
#include "CObjMgr.h"
#include "CBoss.h"
#include "CEffectMgr.h"
#include "CSoundMgr.h"

void CCollisionMgr::Collision_Rect(list<CObj*> DstList, list<CObj*> SrcList)
{
	RECT	rc{};

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

void CCollisionMgr::Collision_Circle(list<CObj*> DstList, list<CObj*> SrcList)
{
	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Circle(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Circle(CObj* pDst, CObj* pSrc)
{
	// fabs : 절대 값을 구하는 용도의 함수

	float		fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList)
{
	float fWidth(0.f), fHeight(0.f);


	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				if (fWidth > fHeight)	// 상하 충돌
				{
					// 상 충돌
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						Dst->Set_PosY(-fHeight);
					}

					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}
				}

				else		// 좌우 충돌
				{
					// 좌 충돌
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						Dst->Set_PosX(-fWidth);
					}

					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pWidth, float* pHeight)
{
	float		fRWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fRHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fRadiusX = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->fCY + pSrc->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX >= fRWidth) && (fRadiusY >= fRHeight))
	{
		*pWidth = fRadiusX - fRWidth;
		*pHeight = fRadiusY - fRHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::RectCollision(const RECT& rectA, const RECT& rectB)
{
	return !(rectA.right < rectB.left || rectA.left > rectB.right ||
		rectA.bottom < rectB.top || rectA.top > rectB.bottom);
}

//void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)							// 바닥에서 안정성 보임(단 다른곳이 뚫림)
//{
//	if (!pPlayer || !pQuadTree)
//		return;
//
//	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
//	std::vector<Tile> tiles;
//	pQuadTree->Query(camRect, tiles); // 현재 화면 타일만 조회
//
//	RECT playerRect = *pPlayer->Get_Rect();
//
//	for (const auto& tile : tiles) 
//	{
//		RECT tileRect = {
//			tile.x - TILECX / 2,
//			tile.y - TILECY / 2,
//			tile.x + TILECX / 2,
//			tile.y + TILECY / 2
//		};
//
//		if (RectCollision(playerRect, tileRect))
//		{
//			int overlapY = playerRect.bottom - tileRect.top;
//			int overlapX = 0;
//
//			if (playerRect.bottom <= tileRect.bottom && playerRect.top < tileRect.top) {
//				// 바닥 위에 있음
//				pPlayer->Set_Pos(pPlayer->Get_Info()->fX, tileRect.top - (playerRect.bottom - playerRect.top) / 2);
//				OutputDebugString(L"[바닥 충돌] 위에서 착지\n");
//			}
//			else if (playerRect.top >= tileRect.top && playerRect.bottom > tileRect.bottom) {
//				// 머리 부딪힘
//				pPlayer->Set_Pos(pPlayer->Get_Info()->fX, tileRect.bottom + (playerRect.bottom - playerRect.top) / 2);
//				OutputDebugString(L"[천장 충돌] 위로 충돌\n");
//			}
//			else if (playerRect.right > tileRect.left && playerRect.left < tileRect.left) {
//				// 왼쪽 벽 충돌
//				pPlayer->Set_Pos(tileRect.left - (playerRect.right - playerRect.left) / 2, pPlayer->Get_Info()->fY);
//				OutputDebugString(L"[오른쪽 충돌] 왼쪽 벽에 부딪힘\n");
//			}
//			else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right) {
//				// 오른쪽 벽 충돌
//				pPlayer->Set_Pos(tileRect.right + (playerRect.right - playerRect.left) / 2, pPlayer->Get_Info()->fY);
//				OutputDebugString(L"[왼쪽 충돌] 오른쪽 벽에 부딪힘\n");
//			}
//		}
//	}
//}

//void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)						// 부들거림이 개선됬으나 아직 있음
//{
//	if (!pPlayer || !pQuadTree)
//		return;
//
//	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
//	std::vector<Tile> tiles;
//	pQuadTree->Query(camRect, tiles); // 현재 화면 타일만 조회
//
//	RECT playerRect = *pPlayer->Get_Rect();
//	float fX = pPlayer->Get_Info()->fX;
//	float fY = pPlayer->Get_Info()->fY;
//	int halfW = (playerRect.right - playerRect.left) / 2;
//	int halfH = (playerRect.bottom - playerRect.top) / 2;
//
//	for (const auto& tile : tiles)
//	{
//		RECT tileRect = {
//			tile.x - TILECX / 2,
//			tile.y - TILECY / 2,
//			tile.x + TILECX / 2,
//			tile.y + TILECY / 2
//		};
//
//		RECT intersect = {};
//		if (IntersectRect(&intersect, &playerRect, &tileRect))
//		{
//			int overlapX = intersect.right - intersect.left;
//			int overlapY = intersect.bottom - intersect.top;
//
//			// 충돌 방향 판별
//			if (overlapY < overlapX)
//			{
//				if (playerRect.bottom > tileRect.top && playerRect.top < tileRect.top)
//				{
//					// 바닥
//					pPlayer->Set_Pos(fX, tileRect.top - halfH);
//					dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//					dynamic_cast<CPlayer*>(pPlayer)->Set_Jump(false);
//					OutputDebugString(L"[바닥 충돌]\n");
//				}
//				else if (playerRect.top < tileRect.bottom && playerRect.bottom > tileRect.bottom)
//				{
//					// 천장
//					pPlayer->Set_Pos(fX, tileRect.bottom + halfH);
//					dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//					OutputDebugString(L"[천장 충돌]\n");
//				}
//			}
//			else
//			{
//				if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
//				{
//					// 왼쪽 벽
//					pPlayer->Set_Pos(tileRect.left - halfW, fY);
//					OutputDebugString(L"[오른쪽 충돌] 왼쪽 벽에 부딪힘\n");
//				}
//				else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
//				{
//					// 오른쪽 벽
//					pPlayer->Set_Pos(tileRect.right + halfW, fY);
//					OutputDebugString(L"[왼쪽 충돌] 오른쪽 벽에 부딪힘\n");
//				}
//			}
//
//			// 위치 변경 후 rect 갱신
//			dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
//			playerRect = *pPlayer->Get_Rect();
//			fX = pPlayer->Get_Info()->fX;
//			fY = pPlayer->Get_Info()->fY;
//		}
//	}
//}

//void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)
//{
//	if (!pPlayer || !pQuadTree)
//		return;
//
//	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
//	std::vector<Tile> tiles;
//	pQuadTree->Query(camRect, tiles);
//
//	float fX = pPlayer->Get_Info()->fX;
//	float fY = pPlayer->Get_Info()->fY;
//	RECT playerRect = *pPlayer->Get_Rect();
//	wchar_t szBuf[256];
//	swprintf(szBuf, 256, L"[충돌 전] X: %.2f, Y: %.2f\n", fX, fY);
//	OutputDebugString(szBuf);
//	int halfW = (playerRect.right - playerRect.left) / 2;
//	int halfH = (playerRect.bottom - playerRect.top) / 2;
//
//	for (const auto& tile : tiles)
//	{
//		RECT tileRect = {
//			tile.x - TILECX / 2,
//			tile.y - TILECY / 2,
//			tile.x + TILECX / 2,
//			tile.y + TILECY / 2
//		};
//
//		if (!RectCollision(playerRect, tileRect))
//			continue;
//
//		int overlapX = min(playerRect.right, tileRect.right) - max(playerRect.left, tileRect.left);
//		int overlapY = min(playerRect.bottom, tileRect.bottom) - max(playerRect.top, tileRect.top);
//
//		if (overlapY < overlapX)
//		{
//			if (playerRect.bottom > tileRect.top && playerRect.top < tileRect.top)
//			{
//				pPlayer->Set_Pos(fX, tileRect.top - halfH);
//				dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//				dynamic_cast<CPlayer*>(pPlayer)->Set_Jump(false);
//			}
//			else if (playerRect.top < tileRect.bottom && playerRect.bottom > tileRect.bottom)
//			{
//				pPlayer->Set_Pos(fX, tileRect.bottom + halfH);
//				dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//			}
//		}
//		else
//		{
//			if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
//			{
//				pPlayer->Set_Pos(tileRect.left - halfW, fY);
//			}
//			else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
//			{
//				pPlayer->Set_Pos(tileRect.right + halfW, fY);
//			}
//		}
//
//		dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
//		playerRect = *pPlayer->Get_Rect();
//		fX = pPlayer->Get_Info()->fX;
//		fY = pPlayer->Get_Info()->fY;
//		swprintf(szBuf, 256, L"[충돌 후] X: %.2f, Y: %.2f\n", fX, fY);
//		OutputDebugString(szBuf);
//	}
//}

//void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)
//{
//	if (!pPlayer || !pQuadTree)
//		return;
//
//	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
//	std::vector<Tile> tiles;
//	pQuadTree->Query(camRect, tiles);
//
//	float fX = pPlayer->Get_Info()->fX;
//	float fY = pPlayer->Get_Info()->fY;
//	RECT playerRect = *pPlayer->Get_Rect();
//	int halfW = (playerRect.right - playerRect.left) / 2;
//	int halfH = (playerRect.bottom - playerRect.top) / 2;
//
//	for (const auto& tile : tiles)
//	{
//		RECT tileRect = {
//			tile.x - TILECX / 2,
//			tile.y - TILECY / 2,
//			tile.x + TILECX / 2,
//			tile.y + TILECY / 2
//		};
//
//		if (!RectCollision(playerRect, tileRect))
//			continue;
//
//		int overlapX = min(playerRect.right, tileRect.right) - max(playerRect.left, tileRect.left);
//		int overlapY = min(playerRect.bottom, tileRect.bottom) - max(playerRect.top, tileRect.top);
//
//		if (overlapY < overlapX)
//		{
//			if (playerRect.bottom > tileRect.top && playerRect.top < tileRect.top)
//			{
//				pPlayer->Set_Pos(pPlayer->Get_Info()->fX, tileRect.top - halfH);
//				dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//				dynamic_cast<CPlayer*>(pPlayer)->Set_Jump(false);
//			}
//			else if (playerRect.top < tileRect.bottom && playerRect.bottom > tileRect.bottom)
//			{
//				pPlayer->Set_Pos(pPlayer->Get_Info()->fX, tileRect.bottom + halfH);
//				dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//			}
//		}
//		else
//		{
//			if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
//			{
//				pPlayer->Set_Pos(tileRect.left - halfW, pPlayer->Get_Info()->fY);
//			}
//			else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
//			{
//				pPlayer->Set_Pos(tileRect.right + halfW, pPlayer->Get_Info()->fY);
//			}
//		}
//
//		dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
//		playerRect = *pPlayer->Get_Rect();
//		/*fX = pPlayer->Get_Info()->fX;
//		fY = pPlayer->Get_Info()->fY;*/
//	}
//}

void CCollisionMgr::Collision_Attack()
{
	list<CObj*>& colliderList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_COLLIDER);
	list<CObj*>& playerList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER);
	list<CObj*>& headList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_HEAD);
	list<CObj*>& monsterList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER);
	list<CObj*>& bossList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOSS);

	for (auto& pCollider : colliderList)
	{
		if (!dynamic_cast<CAttackCollider*>(pCollider)->IsActive())
		{
			//OutputDebugString(L"[충돌 검사 건너뜀] 비활성화 상태\n");
			continue;
		}

		ETeam team = dynamic_cast<CAttackCollider*>(pCollider)->Get_Team();

		/*wchar_t szDebug[128];
		swprintf_s(szDebug, L"[콜라이더 검사 시작] 팀: %d\n", (int)team);
		OutputDebugString(szDebug);*/

		if (team == ETeam::Player)
		{
			CheckCollisionWithTargets(pCollider, monsterList);
			CheckCollisionWithTargets(pCollider, bossList);
		}
		else if (team == ETeam::Enemy)
		{
			CheckCollisionWithTargets(pCollider, playerList);
			CheckCollisionWithTargets(pCollider, headList);
		}
		else if (team == ETeam::Head)
		{
			CheckCollisionWithTargets(pCollider, monsterList);
			CheckCollisionWithTargets(pCollider, bossList);
			CheckHeadCollisionWithPlayer(pCollider, playerList);
		}
	}
}

void CCollisionMgr::CheckHeadCollisionWithPlayer(CObj* pCollider, list<CObj*>& playerList)
{
	RECT rcCollider = *pCollider->Get_Rect();

	for (auto& pTarget : playerList)
	{
		if (pTarget->Get_Dead())
			continue;

		if (RectCollision(rcCollider, *pTarget->Get_Rect()))
		{
			OutputDebugString(L"[머리 - 플레이어 충돌] 쿨 초기화 + 회수\n");
			//dynamic_cast<CPlayer*>(pTarget)->Reset_SkulSkill();
			pCollider->Set_Dead(); // 머리 제거
			break;
		}
	}
}


void CCollisionMgr::CheckCollisionWithTargets(CObj* pCollider, list<CObj*>& targets)
{
	CAttackCollider* pAtkCol = dynamic_cast<CAttackCollider*>(pCollider);
	if (!pAtkCol || !pAtkCol->IsActive())
		return;

	RECT rcCollider = *pCollider->Get_Rect();
	//RECT& playerRect = pPlayer->Get_HitBox()->Get_Rect();

	for (auto& pTarget : targets)
	{
		if (pTarget->Get_Dead())
			continue;

		CHitBox* pHitBox = pTarget->Get_HitBox();
		if (!pHitBox)
			continue;

		//OutputDebugString(L"→ 충돌 검사 대상 접근\n");
		if (CCollisionMgr::RectCollision(rcCollider, pTarget->Get_HitBox()->Get_Rect()))
		{
			if (pAtkCol->Get_Hit(pTarget))
				continue;

			if (!pHitBox->Can_Hit())
				continue;

			OutputDebugString(L"[히트 발생!] \n");
			pAtkCol->Insert_Hit(pTarget);
			pHitBox->Add_Hit();
			pTarget->OnHit(dynamic_cast<CAttackCollider*>(pCollider));
			if (auto au = dynamic_cast<CPlayer*>(pTarget))				// 종류별 설정 필요할듯 맞은게 플레이어일때 보스일때
			{
				dynamic_cast<CPlayer*>(pTarget)->Get_Skul()->PlayHitEffect();
				CSoundMgr::Get_Instance()->Play(L"hit_blood.wav");
			}

			if (auto au = dynamic_cast<CBoss*>(pTarget))
			{
				if (pAtkCol->Get_SkillType() == ESkillType::Attack)
				{
					CEffectMgr::Get_Instance()->Add_Effect(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skul()->GetPlayAttackEffect(), 
						{(float)au->Get_HitBox()->Get_Center().x, (float)au->Get_HitBox()->Get_Center().y});
				}
				else if (pAtkCol->Get_SkillType() == ESkillType::SkillA)
				{
					CEffectMgr::Get_Instance()->Add_Effect(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skul()->GetPlayAttackEffect(),
						{ (float)au->Get_HitBox()->Get_Center().x, (float)au->Get_HitBox()->Get_Center().y });
				}
				else if (pAtkCol->Get_SkillType() == ESkillType::SkillS)
				{
					CEffectMgr::Get_Instance()->Add_Effect(dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Skul()->GetPlaySkillSEffect(),
						{ (float)au->Get_HitBox()->Get_Center().x, (float)au->Get_HitBox()->Get_Center().y });
				}
			}
			pHitBox->Reset_HitCount();
			pHitBox->Set_MaxHits(1);
			pCollider->Set_Dead();
			break;
		}
	}
}

void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)
{
	if (!pPlayer || !pQuadTree)
		return;

	//RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
	RECT camRect = CCameraMgr::Get_Instance()->SetAndGet_ExtendedCameraRect(600, 600);
	std::vector<Tile> tiles;
	pQuadTree->Query(camRect, tiles);

	//RECT playerRect = *pPlayer->Get_Rect();
	RECT& playerRect = pPlayer->Get_HitBox()->Get_Rect();
	int halfW = (playerRect.right - playerRect.left) / 2;
	int halfH = (playerRect.bottom - playerRect.top) / 2;

	// Y축 충돌 먼저 처리
	for (const auto& tile : tiles)
	{
		RECT tileRect = {
			tile.x - TILECX / 2,
			tile.y - TILECY / 2,
			tile.x + TILECX / 2,
			tile.y + TILECY / 2
		};

		if (!RectCollision(playerRect, tileRect))
			continue;

		int overlapX = min(playerRect.right, tileRect.right) - max(playerRect.left, tileRect.left);
		int overlapY = min(playerRect.bottom, tileRect.bottom) - max(playerRect.top, tileRect.top);

		if (overlapY < overlapX) // Y축 충돌 우선
		{
			float curX = pPlayer->Get_Info()->fX;
			const int margin = 0;

			if (playerRect.bottom > tileRect.top - margin && playerRect.top < tileRect.top)
			{
				// 바닥 충돌
				pPlayer->Set_Pos(curX, tileRect.top - halfH);
				pPlayer->Set_Gravity(0.f);
				pPlayer->Set_Jump(false);
				if (auto player = dynamic_cast<CPlayer*>(pPlayer))
				{
					dynamic_cast<CPlayer*>(pPlayer)->Set_JumpCntReset();
				}
				pPlayer->OnTileCollision(tileRect.top - halfH);
				//dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
				//dynamic_cast<CPlayer*>(pPlayer)->Set_Jump(false);
			}
			else if (playerRect.top < tileRect.bottom && playerRect.bottom > tileRect.bottom)
			{
				// 천장 충돌
				pPlayer->Set_Pos(curX, tileRect.bottom + halfH);
				pPlayer->Set_Gravity(0.f);
				//dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
			}

			//dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
			pPlayer->Update_Rect();
			//playerRect = *pPlayer->Get_Rect();
			playerRect = pPlayer->Get_HitBox()->Get_Rect();
		}
	}

	// 최신 위치 기준으로 X축 충돌 따로 처리
	for (const auto& tile : tiles)
	{
		RECT tileRect = {
			tile.x - TILECX / 2,
			tile.y - TILECY / 2,
			tile.x + TILECX / 2,
			tile.y + TILECY / 2
		};

		if (!RectCollision(playerRect, tileRect))
			continue;

		int overlapX = min(playerRect.right, tileRect.right) - max(playerRect.left, tileRect.left);
		int overlapY = min(playerRect.bottom, tileRect.bottom) - max(playerRect.top, tileRect.top);

		float moveDir = pPlayer->Get_Speed();

		//overlapX <= overlapY
		//if (overlapX <= overlapY) // X축 충돌
		//{
		//	float curY = pPlayer->Get_Info()->fY;

		//	if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
		//	{
		//		pPlayer->Set_Pos(tileRect.left - halfW, curY);
		//		//pPlayer->OnTileCollision(tileRect.top - halfH);
		//	}
		//	else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
		//	{
		//		// 오른쪽 벽
		//		pPlayer->Set_Pos(tileRect.right + halfW, curY);
		//		//pPlayer->OnTileCollision(tileRect.top - halfH);
		//	}


		//	//dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
		//	pPlayer->Update_Rect();
		//	//playerRect = *pPlayer->Get_Rect();
		//	playerRect = pPlayer->Get_HitBox()->Get_Rect();
		//}
		const int margin = 6;				// 좌측 : 10(이상 없음), 9(이상 없음), 8(이상 없음), 7(이상 없음), 6(이상 없음), 5(벽에 갇힘)
											// 우측 : 10, 9, 8, 7, 6 -> 다뚫림 5(벽에 갇힘)
		/*const int leftMargin = 10.f;
		const int rightMargin = 15.f;*/
		if (overlapX <= overlapY)
		{
			//float rightGap = abs(playerRect.right - tileRect.left);		// 우측 충돌
			//float leftGap = abs(playerRect.left - tileRect.right);		// 좌측 충돌

			int rightGap = playerRect.right - tileRect.left;		// 우측 충돌
			int leftGap = tileRect.right - playerRect.left;		// 좌측 충돌

			//wchar_t szBuf[128];
			//if (rightGap > 0 && rightGap < 15)  // 우측 충돌 조건 로그
			//{
			//	swprintf_s(szBuf, L"[우측] rightGap: %d, playerRight: %d, tileLeft: %d\n",
			//		rightGap, playerRect.right, tileRect.left);
			//	OutputDebugString(szBuf);
			//}

			//if (leftGap > 0 && leftGap < 15)  // 좌측 충돌 조건 로그
			//{
			//	swprintf_s(szBuf, L"[좌측] leftGap: %d, playerLeft: %d, tileRight: %d\n",
			//		leftGap, playerRect.left, tileRect.right);
			//	OutputDebugString(szBuf);
			//}

			if (rightGap <= margin || leftGap <= margin)
				continue;

			//if (rightGap <= rightMargin)
			//{
			//	pPlayer->Set_Pos(tileRect.left - halfW, pPlayer->Get_Info()->fY);
			//	OutputDebugString(L"[오른쪽 이동 중 + 왼쪽 벽 충돌]\n");
			//}
			//else if (leftGap <= leftMargin)
			//{
			//	pPlayer->Set_Pos(tileRect.right + halfW, pPlayer->Get_Info()->fY);
			//	OutputDebugString(L"[왼쪽 이동 중 + 오른쪽 벽 충돌]\n");
			//}


			// 왼쪽 벽 충돌
			if (playerRect.right >= tileRect.left && playerRect.left < tileRect.left)
			{
				pPlayer->Set_Pos(tileRect.left - halfW, pPlayer->Get_Info()->fY);
				OutputDebugString(L"[오른쪽 이동 중 + 왼쪽 벽 충돌]\n");
			}
			// 오른쪽 벽 충돌
			else if (playerRect.left <= tileRect.right && playerRect.right > tileRect.right)
			{
				pPlayer->Set_Pos(tileRect.right + halfW, pPlayer->Get_Info()->fY);
			}

			pPlayer->Update_Rect();
			playerRect = pPlayer->Get_HitBox()->Get_Rect();
		}
	}
}