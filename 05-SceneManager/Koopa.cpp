#include "Koopa.h"
#include "debug.h"

CKoopa::CKoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;

	SetState(KOOPA_STATE_WALKING);

}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->GetState() == KOOPA_STATE_WALKING)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
	else if (this->GetState() == KOOPA_STATE_IDLING || this->GetState() == KOOPA_STATE_ROLLING)
	{
		left = x - KOOPA_BBOX_SHELL_WIDTH / 2;
		top = y - KOOPA_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPA_BBOX_SHELL_WIDTH;
		bottom = top + KOOPA_BBOX_SHELL_HEIGHT;
	}
	
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;



};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}



void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		if (nx > 0)
		{
			vx = KOOPA_WALKING_SPEED;

		}
		else
		{
			vx = -KOOPA_WALKING_SPEED;

		}
		break;
	case KOOPA_STATE_IDLING:
		vx = 0;
		break;
	case KOOPA_STATE_ROLLING:
		if (nx > 0)
		{
			vx = KOOPA_ROLLING_SPEED;

		}
		else
		{
			vx = -KOOPA_ROLLING_SPEED;

		}
		break;

	}
}



int CKoopa::GetAniId()
{
	int aniId = ID_ANI_KOOPA_WALKINGLEFT;
	if (this->GetState() == KOOPA_STATE_WALKING && nx >0)
	{
		aniId = ID_ANI_KOOPA_WALKINGRIGHT;
	}
	else if (this->GetState() == KOOPA_STATE_WALKING && nx < 0)
	{
		aniId = ID_ANI_KOOPA_WALKINGLEFT;
	}
	else if (this->GetState() == KOOPA_STATE_IDLING)
	{
		aniId = ID_ANI_KOOPA_SHELL_IDLING;
	}
	else if (this->GetState() == KOOPA_STATE_ROLLING)
	{
		aniId = ID_ANI_KOOPA_SHELL_ROLLING;
	}



	return aniId;
}


void CKoopa::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	aniId = GetAniId();

	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
