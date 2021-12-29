#pragma once
#include "Coin.h"
#include "PlayScene.h"
#include "Mario.h"


#define TCOIN_GRAVITY 0.2f 
#define TCOIN_BOUNCING_SPEED 0.2f



#define TCOIN_BBOX_WIDTH 15
#define TCOIN_BBOX_HEIGHT	15

#define ID_ANI_TCOIN 11001

#define TIME_COIN_EXIST 2500

class CTCoin : public CCoin
{
	float start_y;
	int isMultiCoin;
public:
	bool changed;
	ULONGLONG timeExist;
	CTCoin(float x, float y) : CCoin(x, y)
	{
		start_y = y;
		timeExist = GetTickCount64();
		changed = true;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }


	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	void ChangeCoinToBrick();
};