#pragma once
#include "Model.h"

class DragonPortal
{
public:

	DragonPortal();
	~DragonPortal();

	void render();

	// GROUND MODEL FUNCS
	void initDragonPortal();

	// GROUND MODEL VARS
	Model* dragonPortal;
	char* dragonPortalFilePath = "models/dragon_portal.obj";
	char* dragonPortalTexPath = "gfx/textures/DragonJawPortal_Diffuse.jpg";
};

