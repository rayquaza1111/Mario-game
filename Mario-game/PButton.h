#pragma once
#include "GameObject.h"

#define PBUTTON_BBOX_WIDTH			14
#define PBUTTON_BBOX_HEIGHT			14
#define PBUTTON_BBOX_PRESSED_HEIGHT	7

#define ID_ANI_PBUTTON_IDLE		17070
#define ID_ANI_PSWTICH_PRESSED	17071


#define PBUTTON_STATE_IDLE		0
#define PBUTTON_STATE_RISING	1
#define PBUTTON_STATE_PRESSED	2


class CPButton :public CGameObject
{
	float y_start;
public:
	BOOLEAN Pressed_once;
	BOOLEAN isPressed;
	CPButton(float x, float y);

	virtual void Render();


	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void SetState(int state);

	void ChangeBrickToCoin();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};