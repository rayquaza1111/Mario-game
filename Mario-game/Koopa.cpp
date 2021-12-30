#include "Koopa.h"
#include "Goomba.h"
#include "Brick.h"
#include "ColourPlatform.h"

#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"
#include "Leaf.h"
#include "DCoin.h"
#include "Mushroom.h"

CKoopa::CKoopa(float x, float y, int lvl) :CGameObject(x, y)
{
	die_start = -1;
	isBeingHeld = false;
	isVulnerable = false;
	last_state = -1;
	this->level = lvl;
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	wakingUp_timer = -1;
	wakingUp_timeout = -1;
	switch (this->level)
	{
	case 1:
	{
		SetState(KOOPA_STATE_WALKING_LEFT);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid Koopa type: %d\n", this->level);
		return;
	}
}


void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// kill goomba by hit
	if (goomba->GetState() != GOOMBA_STATE_DIE)
		if (state == SHELL_STATE_ROLLING_LEFT || state == SHELL_STATE_ROLLING_RIGHT)
			if (e->nx != 0)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
			}
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (state == SHELL_STATE_ROLLING_LEFT || state == SHELL_STATE_ROLLING_RIGHT)
		if (koopa->GetState() != SHELL_STATE_ROLLING_LEFT || koopa->GetState() != SHELL_STATE_ROLLING_RIGHT)
			return;
	/*if (e->nx != 0)
	{
		koopa->SetState(GOOMBA_STATE_DIE);
	}*/
}

void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	vector<LPGAMEOBJECT> coObjects = ((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->GetObjects();

	if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)

		for (UINT i = 0; i < coObjects.size(); i++)
		{
			if (e->ny < 0 && platform == coObjects[i])
			{
				if (platform == coObjects[i])
				{
					platform = (CPlatform*)coObjects[i];
					if (x <= platform->GetBeginPlatform() - KOOPA_BBOX_WIDTH / 2)
						SetState(KOOPA_STATE_WALKING_RIGHT);
					else if (x + KOOPA_BBOX_WIDTH / 2 >= platform->GetEndPlatform())
						SetState(KOOPA_STATE_WALKING_LEFT);
				}
				vy = 0;
			}
		}
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	vector<LPGAMEOBJECT> coObjects = ((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->GetObjects();

	if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)

		for (UINT i = 0; i < coObjects.size(); i++)
		{
			if (e->ny < 0 && brick == coObjects[i])
			{
				if (brick == coObjects[i])
				{
					brick = (CBrick*)coObjects[i];
					if (x <= brick->GetBeginBrick() - KOOPA_BBOX_WIDTH / 2)
						SetState(KOOPA_STATE_WALKING_RIGHT);
					else if (x + KOOPA_BBOX_WIDTH / 2 >= brick->GetEndBrick())
						SetState(KOOPA_STATE_WALKING_LEFT);
				}
				vy = 0;
			}
		}
	if (state == SHELL_STATE_ROLLING_LEFT || state == SHELL_STATE_ROLLING_RIGHT)
	{
		if (e->nx > 0 || e->nx <0)
		{
			if (brick->GetType() == BRICK_TYPE_QUESTIONCOIN)
			{
				brick->SetState(BRICK_STATE_BOUNCING);
				brick->SetType(BRICK_TYPE_DISABLED);
				CGameObject* obj = NULL;
				obj = new CDCoin(brick->Get_x(), brick->Get_y(), 0);
				obj->SetPosition(brick->Get_x(), brick->Get_y());
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);
			}
			else if (brick->GetType() == BRICK_TYPE_QUESTIONITEM)
			{
				if (level == MARIO_LEVEL_SMALL)
				{
					brick->SetState(BRICK_STATE_BOUNCING);
					brick->SetType(BRICK_TYPE_DISABLED);
					CGameObject* obj = NULL;
					obj = new CMushroom(brick->Get_x(), brick->Get_y());
					obj->SetPosition(brick->Get_x(), brick->Get_y());
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);
				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					brick->SetState(BRICK_STATE_BOUNCING);
					brick->SetType(BRICK_TYPE_DISABLED);
					CGameObject* obj = NULL;
					obj = new CLeaf(brick->Get_x(), brick->Get_y());
					obj->SetPosition(brick->Get_x(), brick->Get_y());
					((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);
				}
			}
			else if (brick->GetType() == BRICK_TYPE_HIDDENCOIN)
			{
				DebugOut(L">>> touch brick %d >>> \n");
				brick->Delete();
			}
		}
	}
}



void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
			if (e->nx > 0)
				SetState(KOOPA_STATE_WALKING_RIGHT);
			else SetState(KOOPA_STATE_WALKING_LEFT);
		else if (state == SHELL_STATE_ROLLING_LEFT || state == SHELL_STATE_ROLLING_RIGHT)
			if (e->nx > 0)
				SetState(SHELL_STATE_ROLLING_RIGHT);
			else SetState(SHELL_STATE_ROLLING_LEFT);
	}
	if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;


	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//Start counting down to wake up
	if ((state == SHELL_STATE_IDLING) && (GetTickCount64() - wakingUp_timer > SHELL_IDLING_TIMEOUT))
	{
		SetState(KOOPA_STATE_WAKING);
		wakingUp_timer = 0;
	}
	//Waking up timeout
	if ((state == KOOPA_STATE_WAKING) && (GetTickCount64() - wakingUp_timeout > KOOPA_STANDUP_TIMEOUT))
	{
		// waking up on ground
		if (!mario->isHolding && !isBeingHeld)
		{
			Wakeup();
		}
		else // waking up on Mario's hands
		{
			mario->Attacked();
			mario->isHolding = false;
			if (mario->Get_nx() > 0)
				SetState(KOOPA_STATE_WALKING_RIGHT);
			else SetState(KOOPA_STATE_WALKING_LEFT);
		}
		isVulnerable = false;
		isBeingHeld = false;
		wakingUp_timeout = 0;
	}


	if (!mario->isHolding && isBeingHeld && isVulnerable)
	{
		isBeingHeld = false;
		isVulnerable = false;
		if (state == SHELL_STATE_IDLING && !isBeingHeld && !isVulnerable)
		{
			nx = mario->Get_nx();
			if (nx > 0)
				SetState(SHELL_STATE_ROLLING_RIGHT);
			else if (nx < 0)
				SetState(SHELL_STATE_ROLLING_LEFT);
		}
	}
	//when being held by mario
	if (isBeingHeld)
	{
		//set height of koopashell
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
			y = mario->Get_y() - 1; //TODO change const number
		else y = mario->Get_y() + 5;
		vy = 0;
		int tmp = mario->Get_nx();
		x = mario->Get_x() + tmp * (MARIO_BIG_BBOX_WIDTH);
		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		{
			if (tmp > 0)
				x = mario->Get_x() + tmp * (MARIO_SMALL_BBOX_WIDTH);
			else
				x = mario->Get_x() + tmp * (KOOPA_BBOX_WIDTH)+3;
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
		}
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = -1;
	if (state == KOOPA_STATE_WALKING_LEFT)
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	else if (state == KOOPA_STATE_WALKING_RIGHT)
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	else if (state == SHELL_STATE_IDLING)
		aniId = ID_ANI_SHELL_IDLING;
	else if (state == SHELL_STATE_ROLLING_LEFT || state == SHELL_STATE_ROLLING_RIGHT)
		aniId = ID_ANI_SHELL_ROLLING;
	else if (state == KOOPA_STATE_WAKING)
		aniId = ID_ANI_KOOPA_WAKING;
	else if (state == KOOPA_STATE_DIE)
		aniId = ID_ANI_KOOPA_WAKING;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SHELL_STATE_IDLING:
		isVulnerable = true;
		wakingUp_timer = GetTickCount64();
		vx = 0;
		y += (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		break;
	case SHELL_STATE_ROLLING_LEFT:
		vx = -SHELL_ROLLING_SPEED;
		break;
	case SHELL_STATE_ROLLING_RIGHT:
		vx = SHELL_ROLLING_SPEED;
		break;
	case KOOPA_STATE_WAKING:
		wakingUp_timeout = GetTickCount64();
		vx = 0;
		break;
	}
}

void CKoopa::Wakeup()
{
	if (state == KOOPA_STATE_WAKING)
	{
		y -= (KOOPA_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		SetState(KOOPA_STATE_WALKING_LEFT);
	}
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SHELL_STATE_IDLING || state == SHELL_STATE_ROLLING_LEFT
		|| state == SHELL_STATE_ROLLING_RIGHT || state == KOOPA_STATE_WAKING)
	{
		left = x - SHELL_BBOX_WIDTH / 2;
		top = y - SHELL_BBOX_HEIGHT / 2;
		right = left + SHELL_BBOX_WIDTH;
		bottom = top + SHELL_BBOX_HEIGHT;
	}
	else if (state == KOOPA_STATE_WALKING_LEFT || state == KOOPA_STATE_WALKING_RIGHT)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}