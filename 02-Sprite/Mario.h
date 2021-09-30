#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#define MARIO_WIDTH 14



class CBrick : public CGameObject {
public: 
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};



class CMario : public CGameObject
{
protected:
	float vx;
public:
	CMario(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};

class CMap : public CGameObject {
protected:
	int  idani;

public:
	CMap(float x, float y, int idani);
	void Render();
	void Update(DWORD dt) {}
	/*int idspirte, idani, top, left, right, bottom;*/
};

