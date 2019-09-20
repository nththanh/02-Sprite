#pragma once
#include "GameObject.h"
class CEnemy : public CGameObject
{
public:
	CEnemy();
	~CEnemy();
	void Update(DWORD dt);
	void Render();
};

