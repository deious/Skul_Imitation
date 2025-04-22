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

//#define DELTA_TIME 0.016f
#define DELTA_TIME (CTimeMgr::Get_Instance()->Get_DeltaTime())


extern HWND    g_hWnd;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };
enum OBJID { OBJ_PRIORITY, OBJ_PLAYER, OBJ_PROJECTILE, OBJ_MONSTER, OBJ_BOSS, OBJ_NPC, OBJ_MOUSE, OBJ_TUTORIAL, OBJ_TRIGGER, OBJ_BUTTON, OBJ_COLLIDER, OBJ_HEAD, OBJ_EFFECT, OBJ_UI, OBJ_END };
enum RENDERID { RENDER_PRIORITY, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_UI, RENDER_MOUSE, RENDER_END };
enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SOUND_END };
enum SKULINFO { SKUL_IDLE, SKUL_WALK, SKUL_ATTACK, SKUL_ATTACK2, SKUL_ATTACK3, SKUL_SKILLA, SKUL_SKILLS, SKUL_ULTIMATE, SKUL_END };

//enum class SkillType
//{
//	Attack,
//	SkillA,
//	SkillB,
//};

enum class EFFECT_TYPE {
	HIT,
	DASH,
	JUMP,
	ATTACK,
	SKILLA,
	SKILLB,
	DIE
};

enum class ESkillType {
	Attack,
	SkillA,
	SkillS,
	SkillD
};

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

typedef struct Vec2
{
	float x, y;

	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

	Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
	Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
	Vec2 operator*(float scalar) const { return Vec2(x * scalar, y * scalar); }

	float Length() const { return sqrtf(x * x + y * y); }

	Vec2 Normalize() const
	{
		float len = Length();
		return (len != 0) ? Vec2(x / len, y / len) : Vec2();
	}
}VEC2;

struct EffectInfo {
	EFFECT_TYPE eType;

	const TCHAR* sFramekey;

	Vec2 vOffset;     // ���� ��ġ (ĳ���� ��ġ + ������)
	Vec2 vSize;       // �ð��� ������ (��, ����)

	int iStartFrame;
	int iEndFrame;
	int iFrameSpeed;
	int iMotion = 0;

	float fScale = 1.f;
	float fRotation = 0.f;

	bool bScreenLock = false;

	CHANNELID eSound;
	RENDERID rId = RENDER_EFFECT;
	bool bPlaySound = false;
};