#include "Tunnel.h"

void CTunnel::Render()
{

	CSprites* s = CSprites::GetInstance();
	s->Get(this->idsprite)->Draw(x, y);
	//RenderBoundingBox();
}

void CTunnel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TUNNEL_BBOX_WIDTH / 2;
	t = y - TUNNEL_BBOX_HEIGHT / 2;
	r = l + TUNNEL_BBOX_WIDTH;
	b = t + TUNNEL_BBOX_HEIGHT;
}
