#include "TemporaryCoin.h"
#include "Brick.h"
#include "PButton.h"
#include "PlayScene.h"



void CTCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TCOIN)->Render(x, y);

	//RenderBoundingBox();
}


void CTCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	CMario* player = ((CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer());



	if (GetTickCount64() - timeExist > TIME_COIN_EXIST && changed == true)
	{
		ChangeCoinToBrick();
		changed = false;
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TCOIN_BBOX_WIDTH / 2;
	t = y - TCOIN_BBOX_HEIGHT / 2;
	r = l + TCOIN_BBOX_WIDTH;
	b = t + TCOIN_BBOX_HEIGHT;
}

void CTCoin::SetState(int state)
{
	CGameObject::SetState(state);

}

void CTCoin::ChangeCoinToBrick()
{
	vector<LPGAMEOBJECT> coObjects = ((LPPLAYSCENE)(CGame::GetInstance()->GetCurrentScene()))->GetObjects();
	for (UINT i = 0; i < coObjects.size(); i++)
	{
		if (dynamic_cast<CTCoin*>(coObjects.at(i)) && !coObjects.at(i)->IsDeleted())
		{
			CTCoin* tcoin = dynamic_cast<CTCoin*>(coObjects.at(i));

				tcoin = (CTCoin*)coObjects[i];
				CGameObject* obj = NULL;
				obj = new CBrick(tcoin->Get_x(), tcoin->Get_y(), BRICK_TYPE_HIDDENCOIN);
				obj->SetPosition(tcoin->Get_x(), tcoin->Get_y());
				tcoin->Delete();
				((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->LoadObject(obj);

		}
	}
}

