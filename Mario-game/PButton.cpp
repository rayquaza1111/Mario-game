#include "PButton.h"
#include "Brick.h"
#include "PlayScene.h"
#include "TemporaryCoin.h"

CPButton::CPButton(float x, float y) : CGameObject(x, y)
{
	y_start = y;
	SetState(PBUTTON_STATE_RISING);
	isPressed = false;
	Pressed_once = false;
}

void CPButton::Render()
{
	int aniId = -1;
	if (state == PBUTTON_STATE_PRESSED)
		aniId = ID_ANI_PSWTICH_PRESSED;
	else
		aniId = ID_ANI_PBUTTON_IDLE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PBUTTON_BBOX_WIDTH / 2;
	t = y - PBUTTON_BBOX_HEIGHT / 2;
	r = l + PBUTTON_BBOX_WIDTH;
	if (state == PBUTTON_STATE_PRESSED)
		b = y + PBUTTON_BBOX_PRESSED_HEIGHT;
	else
		b = y + PBUTTON_BBOX_HEIGHT;
}

void CPButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
		return;
	y += vy * dt;
	CGameObject::Update(dt);
	if (this->y < y_start - 15.0f && GetState() == PBUTTON_STATE_RISING)
		SetState(PBUTTON_STATE_IDLE);
	if (isPressed == true && Pressed_once == false)
	{
		ChangeBrickToCoin();
		Pressed_once = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PBUTTON_STATE_IDLE:
		isPressed = false;
		vy = 0;
		break;
	case PBUTTON_STATE_RISING:
		vy = -0.03f;
		y_start = y;
		break;
	case PBUTTON_STATE_PRESSED:
		vy = 0;
		isPressed = true;
		break;
	}
}


void CPButton::ChangeBrickToCoin()
{
	vector<LPGAMEOBJECT> coObjects = ((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->GetObjects();
	for (UINT i = 0; i < coObjects.size(); i++)
	{
		if (dynamic_cast<CBrick*>(coObjects.at(i)) && !coObjects.at(i)->IsDeleted())
		{
			CBrick* brick = dynamic_cast<CBrick*>(coObjects.at(i));
			if (brick->GetType() == BRICK_TYPE_HIDDENCOIN)
			{
				brick = (CBrick*)coObjects[i];
				CGameObject* obj = NULL;
				obj = new CTCoin(brick->Get_x() , brick->Get_y());
				obj->SetPosition(brick->Get_x() , brick->Get_y());
				brick->Delete();
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);
			}
		}
	}
}

