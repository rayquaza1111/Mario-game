#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "DCoin.h"
#include "Portal.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "PButton.h"
#include "Plant.h"
#include "Bulllet.h"

#include "Collision.h"

CMario* CMario::__instance = NULL;

CMario* CMario::GetInstance()
{
	if (__instance == NULL)
		__instance = new CMario();
	return __instance;
}
CMario::CMario()
{

}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (isAttack)
	{
		if (GetTickCount64() - timeAttack > MARIO_TIME_ATTACK)
		{
			isAttack = false;
		}
	}

	if (isWagging)
	{
		if (GetTickCount64() - timeWagging > MARIO_TIME_WAGGING)
		{
			isWagging = false;
		}
	}


	if (isFlying)
	{
		if (GetTickCount64() - timeFlying > MARIO_TIME_FLYING && isFlying)
		{
			timeFlying = 0;
			isFlying = false;
		}
	}

	HandleMarioEnterPipe();

	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
				vx = 0;
			
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CPButton*>(e->obj))
		OnCollisionWithPButton(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);

}

void CMario::Attacked()
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_RACOON)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}


void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);


	if (e->ny > 0)
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
	}

	if (isAttack && e->nx >0 || isAttack && e->nx < 0)
	{
		if (brick->GetType() == BRICK_TYPE_HIDDENCOIN)
		{
			DebugOut(L">>> touch brick %d >>> \n");
			brick->Delete();
		}
		if (brick->GetType() == BRICK_TYPE_PBUTTON)
		{
			brick->SetType(BRICK_TYPE_DISABLED);
			CGameObject* obj = NULL;
			obj = new CPButton(brick->Get_x() , brick->Get_y());
			obj->SetPosition(brick->Get_x() , brick->Get_y() );
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> make paragoomba a goomba, if there's a goomba, it kills goomba
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{ 
			if (goomba->GetLevel() == 2)
			{
				DebugOut(L">>> GOOMBA LEVEL %d >>> \n", goomba->GetLevel());
				goomba->SetLevel(1);
				goomba->SetState(GOOMBA_STATE_WALKING);
			}
			else 
				goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (isAttack && e->nx !=0)
	{
		untouchable = 1;
		DebugOut(L">>>  touch goomba by x >>> \n");
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (goomba->GetLevel() == 2)
			{
				DebugOut(L">>> GOOMBA LEVEL %d >>> \n", goomba->GetLevel());
				goomba->SetLevel(1);
				goomba->SetState(GOOMBA_STATE_WALKING);
			}
			else
				goomba->SetState(GOOMBA_STATE_DIE);
		}
		untouchable = 0;
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				Attacked();
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* coin = dynamic_cast<CCoin*>(e->obj);
	//DebugOut(L">>Coin state = %d<<\n", coin->GetState());
	if (coin->GetState() == COIN_STATE_IDLE)
	{
		coin->Delete();
		coin++;
	}
}

void CMario::OnCollisionWithPButton(LPCOLLISIONEVENT e)
{
	CPButton* pButton = dynamic_cast<CPButton*>(e->obj);
	if (e->ny < 0)
	{
		DebugOut(L">>> TouchButton >>> \n");
		if (pButton->GetState() != PBUTTON_STATE_PRESSED)
		{
			pButton->SetState(PBUTTON_STATE_PRESSED);
		}
	}
}


void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	if (e->ny > 0 || e->ny < 0)
	{
		DebugOut(L">>> TouchPortal >>> \n");
		/*if (e->ny < 0 && (CGame::GetInstance()->IsKeyDown(DIK_DOWN)))*/
		if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			StartPipeDown();
		}
		if (e->ny > 0 && (CGame::GetInstance()->IsKeyDown(DIK_UP)))
		{
			StartPipeUp();
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (e->ny < 0)
	{
		if (koopa->GetState() != SHELL_STATE_IDLING)
		{
			if (koopa->GetState() == KOOPA_STATE_WALKING_LEFT || koopa->GetState() == KOOPA_STATE_WALKING_RIGHT)
			{
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				koopa->SetState(SHELL_STATE_IDLING);
			}
		}
		
	}
	else if (isAttack)
	{
		koopa->SetState(KOOPA_STATE_DIE);

	}
	else if (koopa->GetState() != SHELL_STATE_IDLING)
		{
			Attacked();
		}
	
	else 
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != SHELL_STATE_IDLING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}

	if (e->nx != 0)
	{
		if (koopa->GetState() == SHELL_STATE_IDLING)
		{
			if ((state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT))
			{
				isHolding = true;
				koopa->isBeingHeld = true;
			}
			else 
			{
				if (e->nx > 0)
					koopa->SetState(SHELL_STATE_ROLLING_LEFT);
				else koopa->SetState(SHELL_STATE_ROLLING_RIGHT);
				SetState(MARIO_STATE_KICK);
				isHolding = false;
				koopa->isBeingHeld = false;
				koopa->isVulnerable = false;
			}
		}
	}
	// kick 
	if (e->nx != 0)
	{
		if (koopa->GetState() == SHELL_STATE_IDLING)
		{
			if (e->nx > 0)
				koopa->SetState(SHELL_STATE_ROLLING_LEFT);
			else koopa->SetState(SHELL_STATE_ROLLING_RIGHT);
		}
	}
	else 
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != SHELL_STATE_IDLING)
				Attacked();
		}
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	
	// Eat mushroom
	if (mushroom->GetState() == MUSHROOM_STATE_MOVING)
	{
		//DebugOut(L"state mushroom: %d \n", mushroom->GetState());
		if (level == MARIO_LEVEL_SMALL)
		{
			SetLevel(MARIO_LEVEL_BIG);
			e->obj->Delete();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			LifeUp();
			e->obj->Delete();
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);

	// Eat mushroom
	if (leaf->GetState() == LEAF_STATE_FALLING)
	{
			SetLevel(MARIO_LEVEL_RACOON);
			e->obj->Delete();
	}
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	CBullet* bullet = dynamic_cast<CBullet*>(e->obj);

	if (e->nx != 0 || e->ny != 0)
	{
		Attacked();
	}
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);

	if (isAttack)
	{
		plant->SetState(PLANT_STATE_DIE);
	}
	else if (e->nx != 0 || e->ny != 0)
	{
		Attacked();
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (isPipeDown || isPipeUp)
		aniId = ID_ANI_MARIO_SMALL_ENTERING_PIPE;
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (isPipeDown || isPipeUp)
		aniId = ID_ANI_MARIO_ENTERING_PIPE;
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (isPipeDown || isPipeUp)
		aniId = ID_ANI_MARIO_RACCOON_ENTERING_PIPE;
	else if (!isOnPlatform)
	{
		if (nx >= 0)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			if (isHolding)
				aniId = ID_ANI_MARIO_RACCOON_HOLDING_JUMP_RIGHT;
		}
		else
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			if (isHolding)
				aniId = ID_ANI_MARIO_RACCOON_HOLDING_JUMP_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SITTING_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SITTING_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0)
				{
					aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLDING_IDLE_RIGHT;
					}
				}
				else
				{
					aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
					if (isHolding)
					{
						aniId = ID_ANI_MARIO_RACCOON_HOLDING_IDLE_LEFT;
					}
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRAKING_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
					if (isHolding)
						aniId = ID_ANI_MARIO_RACCOON_HOLDING_RUN_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else  if (vx < 0)
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRAKING_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
					if (isHolding)
						aniId = ID_ANI_MARIO_RACCOON_HOLDING_RUN_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
	if (isAttack)
	{	
			if (nx > 0)aniId = ID_ANI_MARIO_RACOON_ATTACK_RIGHT;
			else aniId = ID_ANI_MARIO_RACOON_ATTACK_LEFT;
		
	}

	if (isWagging)
	{
		if (nx > 0)aniId = ID_ANI_MARIO_RACCOON_WAGGING_RIGHT;
		else aniId = ID_ANI_MARIO_RACCOON_WAGGING_LEFT;
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
	{
		aniId = GetAniIdBig();
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		aniId = GetAniIdSmall();
	}
	else if (level == MARIO_LEVEL_RACOON)
	{
		aniId = GetAniIdRacoon();
	}

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level == MARIO_LEVEL_BIG)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		if (isOnPlatform && level == MARIO_LEVEL_RACOON)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_RACOON_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_ATTACK:
		isAttack = true;
		timeAttack = GetTickCount64();
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_FLYING:
		timeFlying = GetTickCount64();
		isFlying = true;
		vy = -MARIO_FLY_SPEED;
		break;

	case MARIO_STATE_WAGGING:
		isWagging = true;
		timeWagging = GetTickCount64();
		if (nx > 0)
		{
			vx = MARIO_WAGGING_X;
		}
		else
		{
			vx = -MARIO_WAGGING_X;
		}
		vy = -MARIO_WAGGING_Y;
		break;
	}

	CGameObject::SetState(state);
}



void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACOON) 
	{
		if (isSitting)
		{
			left = x - MARIO_RACOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_SITTING_BBOX_HEIGHT;
		}
		if (isAttack)
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH + MARIO_TAIL_LENGTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::HandleMarioEnterPipe()
{
	if (GetTickCount64() - pipeDown_start < MARIO_PIPE_TIME && isPipeDown)
	{
		vy = 0.03f;
	}
	if (GetTickCount64() - pipeDown_start >= MARIO_PIPE_TIME && isPipeDown)
	{
		if (Get_y() < GROUND)
		{
			DebugOut(L">>> chui cong' >>> \n");
			SwitchArea();
			StartPipeDown();
		}
		else if (Get_y() > GROUND)
		{
			DebugOut(L">>> ngung chui cong' >>> \n");
			StopPipeDown();
		}
	}
	if (GetTickCount64() - pipeUp_start < MARIO_PIPE_TIME && isPipeUp)
	{
		vy = -0.03f;
	}
	if (GetTickCount64() - pipeUp_start >= MARIO_PIPE_TIME && isPipeUp)
	{
		if (Get_y() > GROUND)
		{
			SwitchArea();
			StartPipeUp();
		}
		else if (Get_y() < GROUND)
		{
			StopPipeUp();
		}
	}
}

