#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.0009f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_FLYING_SPEED 0.3f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBARED_BBOX_WIDTH 16
#define GOOMBARED_BBOX_HEIGHT 16


#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_FLYING 300



#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_REDGOOMBA_WALKING 5002
#define ID_ANI_REDGOOMBA_FLYING 5003

#define	GOOMBA_LEVEL_NORMAL	1
#define	GOOMBA_LEVEL_RED	2

class CGoomba : public CGameObject
{

protected:
	float ax;				
	float ay; 
	float start_x;
	float start_y;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int level);
		
	virtual void SetState(int state);
	void SetLevel(int l);
	int level;
	int GetAniIdNormal();
	int GetAniIdRed();
};