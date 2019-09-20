#include "GameObject.h"

class CMisc : public CGameObject
{
public:
	CMisc();
	~CMisc();
	void Update(DWORD dt);
	void Render();
};
