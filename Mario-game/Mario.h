#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.25f


#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0004f
#define MARIO_ACCEL_MAX_X	0.6f

#define MARIO_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_FLY_SPEED 0.4f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_ATTACK	700
#define MARIO_STATE_KICK 701

#define MARIO_STATE_FLYING			800

#define MARIO_STATE_WAGGING		900


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_ENTERING_PIPE		1002

#define ID_ANI_MARIO_DIE 999


// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_ENTERING_PIPE		1699

// RACCOON MARIO

#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT			1701
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT			1700

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT		1801
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT		1800

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT		1901
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT		1900

#define ID_ANI_MARIO_RACCOON_HOLDING_IDLE_RIGHT	1911
#define ID_ANI_MARIO_RACCOON_HOLDING_IDLE_LEFT	1910

#define ID_ANI_MARIO_RACCOON_HOLDING_RUN_RIGHT	1921
#define ID_ANI_MARIO_RACCOON_HOLDING_RUN_LEFT	1920

#define ID_ANI_MARIO_RACCOON_HOLDING_JUMP_RIGHT	1931
#define ID_ANI_MARIO_RACCOON_HOLDING_JUMP_LEFT	1930

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT	2001
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT		2000

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT		2101
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT		2100

#define ID_ANI_MARIO_RACCOON_SITTING_RIGHT		2201
#define ID_ANI_MARIO_RACCOON_SITTING_LEFT		2200


#define ID_ANI_MARIO_RACCOON_BRAKING_RIGHT		2301
#define ID_ANI_MARIO_RACCOON_BRAKING_LEFT		2300

#define ID_ANI_MARIO_RACOON_ATTACK_RIGHT	2400
#define ID_ANI_MARIO_RACOON_ATTACK_LEFT	2401

#define ID_ANI_MARIO_RACCOON_ENTERING_PIPE		2500

#define ID_ANI_MARIO_RACCOON_WAGGING_RIGHT		2600
#define ID_ANI_MARIO_RACCOON_WAGGING_LEFT		2601

#pragma endregion

#define GROUND_Y 160.0f

#define GROUND 432





#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  13
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  13
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_TAIL_LENGTH	0

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  12
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_RACOON_BBOX_WIDTH  20
#define MARIO_RACOON_BBOX_HEIGHT 24
#define MARIO_RACOON_SITTING_BBOX_WIDTH  20
#define MARIO_RACOON_SITTING_BBOX_HEIGHT 16
#define MARIO_RACOON_SIT_HEIGHT_ADJUST ((MARIO_RACOON_BBOX_HEIGHT-MARIO_RACOON_SITTING_BBOX_HEIGHT)/2 - 4 )


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_TIME_ATTACK 240
#define MARIO_TIME_FLYING 2000
#define MARIO_TIME_WAGGING 300
#define MARIO_PIPE_TIME			800

#define MARIO_SPEED_STAGE 7.0f
#define MARIO_SPEED_PHASE 7

#define MARIO_STAND 0.0f

#define MARIO_WAGGING_X	0.05f
#define MARIO_WAGGING_Y	0.03f




class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int life;
	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	
	int coin;
	BOOLEAN isAttack;
	ULONGLONG timeAttack;
	ULONGLONG timeFlying;
	ULONGLONG pipeUp_start;
	ULONGLONG pipeDown_start;
	ULONGLONG timeWagging;
	ULONGLONG flying_start;


	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

	static CMario* __instance;
public:
	BOOLEAN isHolding;
	bool isFlying;
	BOOLEAN isPipeDown = false;
	BOOLEAN isPipeUp = false;
	BOOLEAN isOnPlatform;
	BOOLEAN isWagging;

	static CMario* GetInstance();
	CMario();
	CMario(float x, float y) : CGameObject(x, y)
	{
		state = MARIO_STATE_IDLE;
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		//isOnPlatform = false;
		coin = 0;
		life = 4;
		isHolding = false;
		timeAttack = timeFlying = ULONGLONG(0);
		isFlying = false;
		pipeDown_start = 0;
		pipeUp_start = 0;
		isWagging = false;



	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	
	int GetLevel() { return this->level; }
	void LifeUp() { life++; }
	void CoinUp() { coin++; }

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE && !isPipeDown && !isPipeUp);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Attacked();

	float maxspeed = MARIO_RUNNING_SPEED;
	float GetMaxSpeed() { return this->maxspeed; }
	float GetSpeed() { return this->vx; }
	void SetMaxSpeed() { this->vx = maxspeed; }
	void SetSpeed(float speedset) { this->vx = speedset; }

	void HandleMarioEnterPipe();


	void StartPipeUp()
	{
		pipeUp_start = GetTickCount64();
		isPipeUp = true;
	}
	void StartPipeDown()
	{
		pipeDown_start = GetTickCount64();
		isPipeDown = true;
	}


	void StopPipeUp()
	{
		isPipeUp = false;
		pipeUp_start = 0;
	}
	void StopPipeDown()
	{
		isPipeDown = false;
		pipeDown_start = 0;
	}

	void SwitchArea()
	{
		if (Get_y() < 432)
		{
			SetPosition(2096, 580);
		}
		else
		{
			SetPosition(2272, 352);
		}
	}
};