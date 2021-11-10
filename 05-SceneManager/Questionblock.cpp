#include "Questionblock.h"

CQuestionblock::CQuestionblock(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	y_start = y;
	SetState(QUESTIONBLOCK_STATE_ACTIVE);
}

void CQuestionblock::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	if (this->y < y_start - 12.0f && GetState() == QUESTIONBLOCK_STATE_BOUNCE)
	{
		SetState(QUESTIONBLOCK_STATE_IDLE);
		y = y_start;
	}
};

//void CQuestionblock::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//
//
//}

void CQuestionblock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CQuestionblock::Render()
{
	int aniId = ID_ANI_QUESTIONBLOCK_ACTIVE;
	if (state == QUESTIONBLOCK_STATE_BOUNCE)
	{
		aniId = ID_ANI_QUESTIONBLOCK_IDLE;
	}
	else if (state == QUESTIONBLOCK_STATE_IDLE)
	{
		aniId = ID_ANI_QUESTIONBLOCK_IDLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionblock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTIONBLOCK_STATE_ACTIVE:
		break;
	case QUESTIONBLOCK_STATE_BOUNCE:
		vy = -QUESTIONBLOCK_BOUNCE_SPEED;
		break;
	case QUESTIONBLOCK_STATE_IDLE:
		vy = 0.0f;
		break;
	}
}

void CQuestionblock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}