#pragma once
#include "GameObject.h"
#include "Bulllet.h"

//---------------------------FIRE PLANT
#define ID_ANI_PLANT_LEFT 222221
#define ID_ANI_PLANT_RIGHT 222222




#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 32


#define ATTACK_ZONE 200

#define CONST_X 6
#define CONST_Y 8


#define PLANT_STATE_APPEAR	100
#define PLANT_STATE_INPIPE	200
#define PLANT_STATE_STOP_INPIPE	300
#define PLANT_STATE_STOP_ONPIPE	400
#define PLANT_STATE_FIRE	500
#define PLANT_STATE_DIE 600

#define PLANT_TIME 1000
#define PLANT_TIME_APPEAR 3000
#define PLANT_TIME_INPIPE	2000
#define PLANT_DIE_TIMEOUT 500





#define PLANT_HEIGHT_OFFSET	46

#define PLANT_MOVING_SPEED_Y	0.02f
class CPlant : public CGameObject
{
protected:
	float ax;
	float ay;
	float first_y;
	float second_y;
	float Mario_x;
	float Mario_y;
	ULONGLONG timeWarp;
	ULONGLONG timeWarpAppear;
	ULONGLONG timeAttack;
	ULONGLONG die_start;
	bool isPlantAttack = false;
	bool isAttack = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);


	void AttackZone()
	{
		if (abs(x - Mario_x) <= ATTACK_ZONE)
		{
			calAttack();
		}
	}

	void CreateBullet()
	{
		if (!bullet->isFire)
		{
			if (nx > 0)
			{
				bullet->SetPosition(x + PLANT_BBOX_WIDTH / 2 + CONST_X, y - CONST_Y);
			}
			else
				bullet->SetPosition(x - PLANT_BBOX_WIDTH / 2 - CONST_X, y - CONST_Y);
		}
	}

	void calAttack()
	{
		float vxBullet = 0, vyBullet = 0;

		CreateBullet();

		if (Mario_y < y)
			vyBullet = -VYBULLET;
		else
			vyBullet = VYBULLET;

		if (Mario_x > x)
		{
			vxBullet = VXBULLET;
			nx = 1;
		}
		else
		{
			vxBullet = -VXBULLET;
			nx = -1;
		}

		if (!bullet->isFire)
		{
			bullet->isFire = true;
			bullet->SetSpeed(vxBullet, vyBullet);
			bullet->SetState(BULLET_STATE_OUT_RANGE);
		}

	}

public:
	CBullet* bullet;
	CPlant(float x, float y);
	virtual void SetState(int state);
};