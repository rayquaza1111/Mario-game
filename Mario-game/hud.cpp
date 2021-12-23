#include "hud.h"
#include "PlayScene.h"
#include "Camera.h"
#include "Mario.h"


void CHUD::Render()
{

	float xx = x - 26.0f;
	float yy = y - 4.0f;
	CAnimations::GetInstance()->Get(ID_ANI_HUD_MAIN)->Render(x, y);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	for (int i = 1; i < 7 ; i++)
	{
		if (mario->GetSpeed() > MARIO_RUNNING_SPEED * (i/MARIO_SPEED_STAGE) || mario->GetSpeed()*(-1) > MARIO_RUNNING_SPEED * (i / MARIO_SPEED_STAGE))
		{
			CAnimations::GetInstance()->Get(ID_ANI_STACK_ON)->Render(xx + 9 * i, yy);
		}
	}
	if (mario->GetSpeed() == MARIO_RUNNING_SPEED || mario->GetSpeed() == -MARIO_RUNNING_SPEED)
	{
		CAnimations::GetInstance()->Get(ID_ANI_POWER_ON)->Render(xx + 9 * 7 + 4, yy);
	}
	
}

void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cx, cy;
	CCamera::GetInstance()->GetCamPos(cx, cy);

	x = cx + (HUD_BBOX_WIDTH);
	y = cy + (CGame::GetInstance()->GetBackBufferHeight() - (HUD_BBOX_HEIGHT) / 2);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

}

void CHUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HUD_BBOX_WIDTH / 2;
	top = y - HUD_BBOX_HEIGHT / 2;
	right = left + HUD_BBOX_WIDTH / 2;
	bottom = top + HUD_BBOX_HEIGHT / 2;
}
