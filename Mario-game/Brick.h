#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"


#define BRICK_WIDTH 16

#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15

#define BRICK_BOUNCING_DEFLECT_Y 0.2f

#define BRICK_TYPE_QUESTIONCOIN 1
#define BRICK_TYPE_QUESTIONITEM 2
#define BRICK_TYPE_HIDDENCOIN 3
#define BRICK_TYPE_NORMAL 4
#define BRICK_TYPE_DISABLED 5

#define BRICK_STATE_BOUNCING 10
#define BRICK_STATE_IDLING 20

#define ID_ANI_BRICK_TYPE_DISABLE 10000
#define ID_ANI_BRICK_TYPE_NORMAL 10001
#define ID_ANI_BRICK_TYPE_QUESTION 10002
#define ID_ANI_BRICK_TYPE_HARD 10003

class CBrick : public CGameObject {
	float start_y;
	float start_x;
	int type;
	int itemId;
public:
	CBrick(float x, float y, int _type) : CGameObject(x, y) 
	{ 
		this->type = _type; 
		start_y = y; 
		SetState(BRICK_STATE_IDLING);
		start_x = x;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int isBlocking(){ return 1; }
	virtual int IsCollidable() { return 1; }
	int GetType() { return type; }
	void SetType(int _type) { type = _type; }
	void SetState(int state);

	virtual float GetBeginBrick() { return x; }
	virtual float GetEndBrick() { return (x + 16); }
};