#include "Mushroom.h"
#include "Questionblock.h"


CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	y_start = y;
	SetState(MUSHROOM_STATE_IDLE);
}

void CMushroom::Render()
{
	int aniId = ID_ANI_MUSHROOM;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (this->y < y_start - 16.0f && GetState() == MUSHROOM_STATE_RISING)
	{
		SetState(MUSHROOM_STATE_WALKING);
	}
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == MUSHROOM_STATE_WALKING)
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CMushroom*>(e->obj)) return;

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	}

}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case MUSHROOM_STATE_RISING:
		vx = 0;
		ax = 0;
		vy = -MUSHROOM_RISE_SPEED;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = MUSHROOM_WALKING_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
}
