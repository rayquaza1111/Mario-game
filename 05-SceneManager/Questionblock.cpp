#include "Questionblock.h"

CQuestionblock::CQuestionblock(float x, float y):CGameObject(x, y)
{
	
	SetState(QUESTIONBLOCK_STATE_ACTIVE);
}


void CQuestionblock::Render()
{
	int aniId = ID_ANI_QUESTIONBLOCK_ACTIVE;
	if (state == QUESTIONBLOCK_STATE_IDLE)
	{
		aniId = ID_ANI_QUESTIONBLOCK_IDLE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionblock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTIONBLOCK_STATE_ACTIVE:
		break;
	case QUESTIONBLOCK_STATE_IDLE:
		break;
	}
}

void CQuestionblock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}