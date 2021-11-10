#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int level):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	start_x = x;
	start_y = y;
	SetState(GOOMBA_STATE_FLYING);
	SetLevel(level);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
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

	/*if (this->level == GOOMBA_LEVEL_RED && nx > 0 && x - start_x > 2.0f)
	{
		SetState(GOOMBA_STATE_FLYING);
	}*/
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
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
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
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
			if (nx > 0)
			{
				vx = GOOMBA_WALKING_SPEED;
				vy = -GOOMBA_FLYING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}

			/*if (this->y < start_y - 5.0f)
			{
				vy = 0;
			}
			else
			{
				vy = -GOOMBA_FLYING_SPEED;
			}*/
	
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
	int aniId = -1;
	if (vy < 0)
	{
		aniId = ID_ANI_REDGOOMBA_FLYING;
	}
	else
	{
		aniId = ID_ANI_REDGOOMBA_WALKING;
	}

	if (aniId == -1) aniId = ID_ANI_REDGOOMBA_WALKING;

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
