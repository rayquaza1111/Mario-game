#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MUSHROOM 110001

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f
#define MUSHROOM_RISE_SPEED 0.01f

#define MUSHROOM_STATE_IDLE 100
#define MUSHROOM_STATE_RISING 200
#define MUSHROOM_STATE_WALKING 300

#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

class CMushroom : public CGameObject {
protected:
	float ax, ay;
	float y_start;
public:
	CMushroom(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable()
	{
		return 1;
	};
	virtual void SetState(int state);
};