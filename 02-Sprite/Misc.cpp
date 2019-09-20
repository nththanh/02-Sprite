#include "Misc.h"



CMisc::CMisc()
{
	vx = .07f;
}


CMisc::~CMisc()
{
}

void CMisc::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void CMisc::Render()
{
	CGameObject::Render();
}
