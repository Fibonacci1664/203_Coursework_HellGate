/*
 * About this class
 *		- Dragon portal object is a loaded model
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Model.h"

///////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////