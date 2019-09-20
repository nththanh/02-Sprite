#include "Enemy.h"



CEnemy::CEnemy()
{
	vx = 0.03f;
}


CEnemy::~CEnemy()
{
}

void CEnemy::Update(DWORD dt)
{
	x += vx * dt;
	if ((vx > 0 && x > 255) || (x < 0 && vx < 0)) vx = -vx;
}

void CEnemy::Render()
{
	CGameObject::Render();
}
