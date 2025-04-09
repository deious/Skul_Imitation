#include "pch.h"
#include "CCollisionMgr.h"
#include "CCameraMgr.h"
#include "CPlayer.h"

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

void CCollisionMgr::PlayerToTile(CObj* pPlayer, CQuadTree* pQuadTree)
{
	if (!pPlayer || !pQuadTree)
		return;

	RECT camRect = CCameraMgr::Get_Instance()->Get_CameraRect();
	std::vector<Tile> tiles;
	pQuadTree->Query(camRect, tiles);

	RECT playerRect = *pPlayer->Get_Rect();
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

			if (playerRect.bottom > tileRect.top && playerRect.top < tileRect.top)
			{
				// �ٴ� �浹
				pPlayer->Set_Pos(curX, tileRect.top - halfH);
				dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
				dynamic_cast<CPlayer*>(pPlayer)->Set_Jump(false);
			}
			else if (playerRect.top < tileRect.bottom && playerRect.bottom > tileRect.bottom)
			{
				// õ�� �浹
				pPlayer->Set_Pos(curX, tileRect.bottom + halfH);
				dynamic_cast<CPlayer*>(pPlayer)->Set_Gravity(0.f);
			}

			dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
			playerRect = *pPlayer->Get_Rect();
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

		if (overlapX <= overlapY) // X�� �浹
		{
			float curY = pPlayer->Get_Info()->fY;

			if (playerRect.right > tileRect.left && playerRect.left < tileRect.left)
			{
				// ���� ��
				pPlayer->Set_Pos(tileRect.left - halfW, curY);
			}
			else if (playerRect.left < tileRect.right && playerRect.right > tileRect.right)
			{
				// ������ ��
				pPlayer->Set_Pos(tileRect.right + halfW, curY);
			}

			dynamic_cast<CPlayer*>(pPlayer)->Update_PlayerRect();
			playerRect = *pPlayer->Get_Rect();
		}
	}
}