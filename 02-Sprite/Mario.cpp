#include "Mario.h"


CMario::CMario()
{
	vx = .08f;
}


CMario::~CMario()
{
}

void CMario::Update(DWORD dt)
{
	x += vx * dt;
	y += vx * dt;
	if ((vx > 0 && x > 290) || (x < 0 && vx < 0) || (vx > 0 && y > 175)) vx = -vx;
}

void CMario::Render()
{
	CGameObject::Render();
}
