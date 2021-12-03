#include "Brick.h"
#include "Mushroom.h"
#include "DCoin.h"
#include "debug.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	
	if (type == BRICK_TYPE_DISABLED)
		aniId = ID_ANI_BRICK_TYPE_DISABLE;
	else if (type == BRICK_TYPE_NORMAL)
		aniId = ID_ANI_BRICK_TYPE_NORMAL;
	else if (type == BRICK_TYPE_QUESTIONCOIN)
		aniId = ID_ANI_BRICK_TYPE_QUESTION;
	else if (type == BRICK_TYPE_QUESTIONITEM)
		aniId = ID_ANI_BRICK_TYPE_QUESTION;
	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}



void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (this->y < start_y - 8.0f && GetState() == BRICK_STATE_BOUNCING)
	{
		vy = BRICK_BOUNCING_DEFLECT_Y;
	}
	if (this->y > start_y - 1 && GetState() == BRICK_STATE_BOUNCING)
	{
		//y = start_y;
		//CGameObject* obj = NULL;
		SetState(BRICK_STATE_IDLING);

	/*	if (this->type == BRICK_TYPE_QUESTIONCOIN)
		{
			obj = new CDCoin(x, y, 0);
		}
		else if(this->type == BRICK_TYPE_QUESTIONITEM)
		{
		}
		obj->SetPosition(x, y);
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);*/
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_STATE_IDLING:
		vy = 0.0f;
		x = start_x;
		y = start_y;
		break;
	case BRICK_STATE_BOUNCING:
		vy = - BRICK_BOUNCING_DEFLECT_Y;
		break;
	}
}



void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}