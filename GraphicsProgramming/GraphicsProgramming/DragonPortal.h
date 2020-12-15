#pragma once
#include "Model.h"

class DragonPortal
{
public:

	DragonPortal();
	~DragonPortal();

	void render();

private:

	void initDragonPortal();

	Model* dragonPortal;
	char* dragonPortalFilePath = "models/dragon_portal.obj";
	char* dragonPortalTexPath = "gfx/textures/DragonJawPortal_Diffuse.jpg";
};

