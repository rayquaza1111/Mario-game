#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16
#define QUESTIONBLOCK_BOUNCE_SPEED 0.2f

#define QUESTIONBLOCK_STATE_ACTIVE 100
#define QUESTIONBLOCK_STATE_IDLE 200
#define QUESTIONBLOCK_STATE_BOUNCE 300

#define ID_ANI_QUESTIONBLOCK_ACTIVE 60001
#define ID_ANI_QUESTIONBLOCK_IDLE 60002

class CQuestionblock : public CGameObject {
protected:
	float ax, ay;
	float y_start;
public:
	CQuestionblock(float x, float y);
	void Render();
	//void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
	virtual int IsBlocking() { return 1; }
	virtual int IsCollidable()
	{
		return 1;
	};
};