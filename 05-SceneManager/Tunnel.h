#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TUNNEL_WIDTH 16
#define TUNNEL_BBOX_WIDTH 16
#define TUNNEL_BBOX_HEIGHT 16

class CTunnel : public CGameObject {
protected:
	int idsprite;
public:
	CTunnel(float x, float y, int id_sprite) : CGameObject(x, y)
	{
		this->idsprite = id_sprite;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};