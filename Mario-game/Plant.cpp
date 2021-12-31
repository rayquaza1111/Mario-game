#include "Plant.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"

CPlant::CPlant(float x, float y) :CGameObject(x, y)
{
	first_y = y;
	second_y = y;
	SetState(PLANT_STATE_APPEAR);
	bullet = new CBullet(x, y);
	die_start = -1;
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - PLANT_BBOX_WIDTH / 2;
		top = y - PLANT_BBOX_HEIGHT / 2;
		right = left + PLANT_BBOX_WIDTH;
		bottom = top + PLANT_BBOX_HEIGHT;
}

void CPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{


}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	Mario_x = mario->Get_x();
	Mario_y = mario->Get_y();
	if (Mario_x >= this->x) {
		nx = 1;
	}
	else {
		nx = -1;
	}



	if (state == PLANT_STATE_APPEAR)
	{

		if (y > first_y + PLANT_HEIGHT_OFFSET) {
			SetState(PLANT_STATE_STOP_ONPIPE);
		}
	}
	else if (state == PLANT_STATE_INPIPE)
	{
		if (y < first_y) {
			SetState(PLANT_STATE_STOP_INPIPE);
		}
	}

	if (state == PLANT_STATE_STOP_ONPIPE)
	{
		if (GetTickCount64() - timeWarpAppear > PLANT_TIME_APPEAR)
		{
			SetState(PLANT_STATE_INPIPE);
		}
	}
	else if (state == PLANT_STATE_STOP_INPIPE)
	{
		AttackZone();
		if (GetTickCount64() - timeWarp > PLANT_TIME_INPIPE)
		{
			SetState(PLANT_STATE_APPEAR);
		}
	}

	if (bullet->isFire)
	{
		bullet->Update(dt, coObjects);
	}

	if ((state == PLANT_STATE_DIE) && (GetTickCount64() - die_start > PLANT_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}


	//DebugOut(L"state: %d\n", state);
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlant::Render()
{
	int aniId = -1;

	if (nx > 0)
	{
		if (Mario_y < y) 
		{
			aniId = ID_ANI_PLANT_RIGHT;
		}
		else if (state == PLANT_STATE_DIE)
		{
			aniId = ID_ANI_PLANT_RIGHT;
		}
		else
			aniId = ID_ANI_PLANT_RIGHT;
	}
	else
	{
		if (Mario_y < y)
		{
			aniId = ID_ANI_PLANT_LEFT;
		}
		else if(state == PLANT_STATE_DIE)
		{
			aniId = ID_ANI_PLANT_LEFT;
		}
		else
			aniId = ID_ANI_PLANT_LEFT;
	}

	
	
	

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	if (bullet->isFire)
	{
		bullet->Render();
	}
	//RenderBoundingBox();
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANT_STATE_APPEAR:
		vy = PLANT_MOVING_SPEED_Y;
		break;
	case PLANT_STATE_INPIPE:
		vy = -PLANT_MOVING_SPEED_Y;
		break;
	case PLANT_STATE_STOP_ONPIPE:
		vy = 0;
		timeWarpAppear = GetTickCount64();
	case PLANT_STATE_STOP_INPIPE:
		vy = 0;
		timeWarp = GetTickCount64();
		break;
	case PLANT_STATE_FIRE:
		break;
	case PLANT_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		break;
	}
}