#pragma once

#define WINCX 800
#define WINCY 600

#define	PI		3.141592f
#define PURE		= 0

#define	NOEVENT		0
#define DEAD		1

#define VK_MAX		0xff

#define TILECX		32 
#define TILECY		32

#define TILEX		100
#define TILEY		100

#define DELTA_TIME 0.016f


extern HWND    g_hWnd;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_BOSS, OBJ_MOUSE, OBJ_SHIELD, OBJ_BUTTON, OBJ_COLLIDER, OBJ_END };
enum RENDERID { RENDER_PRIORITY, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_UI, RENDER_END };

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

struct DeleteMap
{
	template<typename T>
	void operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};


typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;

typedef struct tagLinePoint
{


	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY)
		:fX(_fX), fY(_fY) {}

	float		fX, fY;

}LINEPOINT;

typedef struct tagLine
{
	tagLinePoint	tLeft;
	tagLinePoint	tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(tagLinePoint& _tLeft, tagLinePoint& _tRight)
		: tLeft(_tLeft), tRight(_tRight)
	{

	}

}LINE;

typedef struct tagFrame
{
	int		iStart;		// �� �� �ε������� ���
	int		iEnd;		// �� �� �ε������� ���
	int		iMotion;	// �� �� ����� ���
	ULONGLONG	dwFrameSpeed; // �ִϸ��̼��� ���� �ӵ�
	ULONGLONG	dwTime;		// �ִϸ��̼� ���� �ð�

}FRAME;