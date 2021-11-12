#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.001f
#define KOOPA_WALKING_SPEED 0.03f
#define KOOPA_ROLLING_SPEED 0.4f



#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 23
#define KOOPA_BBOX_SHELL_WIDTH 16
#define KOOPA_BBOX_SHELL_HEIGHT 16


#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_IDLING 200
#define KOOPA_STATE_ROLLING 300



#define ID_ANI_KOOPA_WALKINGLEFT 120001
#define ID_ANI_KOOPA_WALKINGRIGHT 120002
#define ID_ANI_KOOPA_SHELL_IDLING 120003
#define ID_ANI_KOOPA_SHELL_ROLLING 120004



class CKoopa : public CGameObject
{
private:
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);

protected:
	float ax;
	float ay;






public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	CKoopa(float x, float y);
	virtual void SetState(int state);

	int GetAniId();



	int nx;


};