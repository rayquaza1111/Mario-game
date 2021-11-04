#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

#define QUESTIONBLOCK_STATE_ACTIVE 100
#define QUESTIONBLOCK_STATE_IDLE 200

#define ID_ANI_QUESTIONBLOCK_ACTIVE 60001
#define ID_ANI_QUESTIONBLOCK_IDLE 60002

class CQuestionblock : public CGameObject {
public:
	CQuestionblock(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};