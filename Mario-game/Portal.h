#pragma once

#include "GameObject.h"


class CPortal : public CGameObject
{
	int scene_id;

	float width;
	float height;

	int zone;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	void RenderBoundingBox(void);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
	int IsBlocking() { return 0; }
};