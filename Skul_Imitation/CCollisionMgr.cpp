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
	// fabs : ���� ���� ���ϴ� �뵵�� �Լ�

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
				if (fWidth > fHeight)	// ���� �浹
				{
					// �� �浹
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						Dst->Set_PosY(-fHeight);
					}

					// �� �浹
					else
					{
						Dst->Set_PosY(fHeight);
					}
				}

				else		// �¿� �浹
				{
					// �� �浹
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						Dst->Set_PosX(-fWidth);
					}

					// �� �浹
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

//void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)							// �ٴڿ��� ������ ����(�� �ٸ����� �ո�)
//{
//	if (!pPlayer || !pQuadTree)
//		return;
//
//	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
//	std::vector<Tile> tiles;
//	pQuadTree->Query(camRect, tiles); // ���� ȭ�� Ÿ�ϸ� ��ȸ
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
//				// �ٴ� ���� ����
//				pPlayer->Set_Pos(pPlayer->Get_Info()->fX, tileRect.top - (playerRect.bottom - playerRect.top) / 2);
//				OutputDebugString(L"[�ٴ� �浹] ������ ����\n");
//			}
//			else if (playerRect.top >= tileRect.top && playerRect.bottom > tileRect.bottom) {
//				// �Ӹ� �ε���
//				pPlayer->Set_Pos(pPlayer->Get_Info()->fX, tileRect.bottom + (playerRect.bottom - playerRect.top) / 2);
//				OutputDebugString(L"[õ�� �浹] ���� �浹\n");
//			}
//			else if (playerRect.right > tileRect.left && playerRect.left < tileRect.left) {
//				// ���� �� �浹
//				pPlayer->Set_Pos(tileRect.left - (playerRect.right - playerRect.left) / 2, pPlayer->Get_Info()->fY);
//				OutputDebugString(L"[������ �浹] ���� ���� �ε���\n");
//			}
//			else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right) {
//				// ������ �� �浹
//				pPlayer->Set_Pos(tileRect.right + (playerRect.right - playerRect.left) / 2, pPlayer->Get_Info()->fY);
//				OutputDebugString(L"[���� �浹] ������ ���� �ε���\n");
//			}
//		}
//	}
//}

//void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)						// �ε�Ÿ��� ���������� ���� ����
//{
//	if (!pPlayer || !pQuadTree)
//		return;
//
//	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
//	std::vector<Tile> tiles;
//	pQuadTree->Query(camRect, tiles); // ���� ȭ�� Ÿ�ϸ� ��ȸ
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
//			// �浹 ���� �Ǻ�
//			if (overlapY < overlapX)
//			{
//				if (playerRect.bottom > tileRect.top && playerRect.top < tileRect.top)
//				{
//					// �ٴ�
//					pPlayer->Set_Pos(fX, tileRect.top - halfH);
//					dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//					dynamic_cast<CPlayer*>(pPlayer)->Set_Jump(false);
//					OutputDebugString(L"[�ٴ� �浹]\n");
//				}
//				else if (playerRect.top < tileRect.bottom && playerRect.bottom > tileRect.bottom)
//				{
//					// õ��
//					pPlayer->Set_Pos(fX, tileRect.bottom + halfH);
//					dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
//					OutputDebugString(L"[õ�� �浹]\n");
//				}
//			}
//			else
//			{
//				if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
//				{
//					// ���� ��
//					pPlayer->Set_Pos(tileRect.left - halfW, fY);
//					OutputDebugString(L"[������ �浹] ���� ���� �ε���\n");
//				}
//				else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
//				{
//					// ������ ��
//					pPlayer->Set_Pos(tileRect.right + halfW, fY);
//					OutputDebugString(L"[���� �浹] ������ ���� �ε���\n");
//				}
//			}
//
//			// ��ġ ���� �� rect ����
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
//	swprintf(szBuf, 256, L"[�浹 ��] X: %.2f, Y: %.2f\n", fX, fY);
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
//		swprintf(szBuf, 256, L"[�浹 ��] X: %.2f, Y: %.2f\n", fX, fY);
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
			//OutputDebugString(L"[�浹 �˻� �ǳʶ�] ��Ȱ��ȭ ����\n");
			continue;
		}

		ETeam team = dynamic_cast<CAttackCollider*>(pCollider)->Get_Team();

		/*wchar_t szDebug[128];
		swprintf_s(szDebug, L"[�ݶ��̴� �˻� ����] ��: %d\n", (int)team);
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
			OutputDebugString(L"[�Ӹ� - �÷��̾� �浹] �� �ʱ�ȭ + ȸ��\n");
			//dynamic_cast<CPlayer*>(pTarget)->Reset_SkulSkill();
			pCollider->Set_Dead(); // �Ӹ� ����
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

		//OutputDebugString(L"�� �浹 �˻� ��� ����\n");
		if (CCollisionMgr::RectCollision(rcCollider, pTarget->Get_HitBox()->Get_Rect()))
		{
			if (pAtkCol->Get_Hit(pTarget))
				continue;

			if (!pHitBox->Can_Hit())
				continue;

			OutputDebugString(L"[��Ʈ �߻�!] \n");
			pAtkCol->Insert_Hit(pTarget);
			pHitBox->Add_Hit();
			pTarget->OnHit(dynamic_cast<CAttackCollider*>(pCollider));
			if (auto au = dynamic_cast<CPlayer*>(pTarget))				// ������ ���� �ʿ��ҵ� ������ �÷��̾��϶� �����϶�
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

	// Y�� �浹 ���� ó��
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

		if (overlapY < overlapX) // Y�� �浹 �켱
		{
			float curX = pPlayer->Get_Info()->fX;
			const int margin = 0;

			if (playerRect.bottom > tileRect.top - margin && playerRect.top < tileRect.top)
			{
				// �ٴ� �浹
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
				// õ�� �浹
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

	// �ֽ� ��ġ �������� X�� �浹 ���� ó��
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
		//if (overlapX <= overlapY) // X�� �浹
		//{
		//	float curY = pPlayer->Get_Info()->fY;

		//	if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
		//	{
		//		pPlayer->Set_Pos(tileRect.left - halfW, curY);
		//		//pPlayer->OnTileCollision(tileRect.top - halfH);
		//	}
		//	else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
		//	{
		//		// ������ ��
		//		pPlayer->Set_Pos(tileRect.right + halfW, curY);
		//		//pPlayer->OnTileCollision(tileRect.top - halfH);
		//	}


		//	//dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
		//	pPlayer->Update_Rect();
		//	//playerRect = *pPlayer->Get_Rect();
		//	playerRect = pPlayer->Get_HitBox()->Get_Rect();
		//}
		const int margin = 6;				// ���� : 10(�̻� ����), 9(�̻� ����), 8(�̻� ����), 7(�̻� ����), 6(�̻� ����), 5(���� ����)
											// ���� : 10, 9, 8, 7, 6 -> �ٶո� 5(���� ����)
		/*const int leftMargin = 10.f;
		const int rightMargin = 15.f;*/
		if (overlapX <= overlapY)
		{
			//float rightGap = abs(playerRect.right - tileRect.left);		// ���� �浹
			//float leftGap = abs(playerRect.left - tileRect.right);		// ���� �浹

			int rightGap = playerRect.right - tileRect.left;		// ���� �浹
			int leftGap = tileRect.right - playerRect.left;		// ���� �浹

			//wchar_t szBuf[128];
			//if (rightGap > 0 && rightGap < 15)  // ���� �浹 ���� �α�
			//{
			//	swprintf_s(szBuf, L"[����] rightGap: %d, playerRight: %d, tileLeft: %d\n",
			//		rightGap, playerRect.right, tileRect.left);
			//	OutputDebugString(szBuf);
			//}

			//if (leftGap > 0 && leftGap < 15)  // ���� �浹 ���� �α�
			//{
			//	swprintf_s(szBuf, L"[����] leftGap: %d, playerLeft: %d, tileRight: %d\n",
			//		leftGap, playerRect.left, tileRect.right);
			//	OutputDebugString(szBuf);
			//}

			if (rightGap <= margin || leftGap <= margin)
				continue;

			//if (rightGap <= rightMargin)
			//{
			//	pPlayer->Set_Pos(tileRect.left - halfW, pPlayer->Get_Info()->fY);
			//	OutputDebugString(L"[������ �̵� �� + ���� �� �浹]\n");
			//}
			//else if (leftGap <= leftMargin)
			//{
			//	pPlayer->Set_Pos(tileRect.right + halfW, pPlayer->Get_Info()->fY);
			//	OutputDebugString(L"[���� �̵� �� + ������ �� �浹]\n");
			//}


			// ���� �� �浹
			if (playerRect.right >= tileRect.left && playerRect.left < tileRect.left)
			{
				pPlayer->Set_Pos(tileRect.left - halfW, pPlayer->Get_Info()->fY);
				OutputDebugString(L"[������ �̵� �� + ���� �� �浹]\n");
			}
			// ������ �� �浹
			else if (playerRect.left <= tileRect.right && playerRect.right > tileRect.right)
			{
				pPlayer->Set_Pos(tileRect.right + halfW, pPlayer->Get_Info()->fY);
			}

			pPlayer->Update_Rect();
			playerRect = pPlayer->Get_HitBox()->Get_Rect();
		}
	}
}