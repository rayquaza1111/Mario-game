#include "Goomba.h"
#include "debug.h"

#include "Koopa.h"

CGoomba::CGoomba(float x, float y, int level) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->nx = -1;

	die_start = -1;
	start_y = y;
	SetState(GOOMBA_STATE_WALKING);
	SetLevel(level);
	mark_x = 0;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->level == GOOMBA_LEVEL_NORMAL)
	{
		if (state == GOOMBA_STATE_DIE)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
		}
		if (state == GOOMBA_STATE_WALKING)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
		else
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}
	if (this->level == GOOMBA_LEVEL_RED)
	{
		left = x - GOOMBARED_BBOX_WIDTH / 2;
		top = y - GOOMBARED_BBOX_HEIGHT / 2;
		right = left + GOOMBARED_BBOX_WIDTH;
		bottom = top + GOOMBARED_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;



	if (mark_x == 20 && level == 2)
	{
		SetState(GOOMBA_STATE_BOUNCE);
		if (this->y < start_y - 10.0f)
		{
			SetState(GOOMBA_STATE_WALKING);
		}
		mark_x++;
	}

	if (mark_x == 40 && level == 2)
	{
		SetState(GOOMBA_STATE_BOUNCE);
		if (this->y < start_y - 10.0f)
		{
			SetState(GOOMBA_STATE_WALKING);
		}
		mark_x++;
	}



	if (mark_x == 60 && level == 2)
	{
		SetState(GOOMBA_STATE_FLYING);
		if (this->y < start_y - 28.0f)
		{
			SetState(GOOMBA_STATE_WALKING);
		}
		mark_x = 0;
	}
	else
	{
		mark_x++;
		if (this->y < start_y - 28.0f)
		{
			SetState(GOOMBA_STATE_WALKING);

			mark_x = 0;
		}
	}

};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}



void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		if (nx > 0)
		{
			vx = GOOMBA_WALKING_SPEED;

		}
		else
		{
			vx = -GOOMBA_WALKING_SPEED;

		}
		break;
	case GOOMBA_STATE_FLYING:
		if (vx > 0)
		{
			nx = 1;
		}
		else
		{
			nx = -1;
		}
		vy = -GOOMBA_FLYING_SPEED;
		break;
	case GOOMBA_STATE_BOUNCE:
		if (vx > 0)
		{
			nx = 1;
		}
		else
		{
			nx = -1;
		}
		vy = -GOOMBA_BOUNCE_SPEED;
		break;


	}
}

void CGoomba::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == GOOMBA_LEVEL_NORMAL)
	{
		y -= (GOOMBARED_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT) / 2;
	}
	level = l;
}

int CGoomba::GetAniIdNormal()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	return aniId;
}

int CGoomba::GetAniIdRed()
{
	int aniId = ID_ANI_REDGOOMBA_WALKING;
	if (this->GetState() == GOOMBA_STATE_FLYING)
	{
		aniId = ID_ANI_REDGOOMBA_FLYING;
	}
	else if (this->GetState() == GOOMBA_STATE_BOUNCE)
	{
		aniId = ID_ANI_REDGOOMBA_BOUNCING;
	}
	else
	{
		aniId = ID_ANI_REDGOOMBA_WALKING;
	}


	return aniId;
}



void CGoomba::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == GOOMBA_STATE_DIE)
		aniId = ID_ANI_GOOMBA_DIE;
	else if (level == GOOMBA_LEVEL_RED)
		aniId = GetAniIdRed();
	else if (level == GOOMBA_LEVEL_NORMAL)
		aniId = GetAniIdNormal();

	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
