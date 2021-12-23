#pragma once
#include "GameObject.h"
#include "debug.h"

#define HUD_BBOX_WIDTH 153
#define HUD_BBOX_HEIGHT 30

#define ID_ANI_HUD_MAIN 81000
#define	ID_ANI_STACK_OFF 81001
#define	ID_ANI_STACK_ON 81002
#define	ID_ANI_POWER_ON 81003
#define	ID_ANI_POWER_OFF 81004

class CHUD : public CGameObject
{
	int speedStack = 0;
public:
	CHUD(float x, float y) : CGameObject(x, y)
	{
		DebugOut(L"init\n");
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//void SetState(int state);
};
