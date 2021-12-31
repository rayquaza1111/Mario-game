#include "Bulllet.h"
#include "Mario.h"
#include "PlayScene.h"

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_WIDTH / 2;
	right = left + BULLET_WIDTH;
	top = y - BULLET_HEIGHT / 2;
	bottom = top + BULLET_HEIGHT;
}


void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (state == BULLET_STATE_OUT_RANGE)
	{
		if (GetTickCount64() - timeDelete > TIME_DELETE_BULLET)
		{
			isFire = false;
		}
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ID_ANI_BULLET)->Render(x, y);

	RenderBoundingBox();
}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (e->nx != 0 || e->ny != 0)
	{
		mario->Attacked();
	}
}

void CBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_OUT_RANGE:
		timeDelete = GetTickCount64();
		break;
	}

}