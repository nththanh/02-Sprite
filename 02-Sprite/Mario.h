#pragma once
#include "GameObject.h"

using namespace std;

class CMario : public CGameObject
{
public:
	CMario();
	~CMario();
	void Update(DWORD dt);
	void Render();
};

