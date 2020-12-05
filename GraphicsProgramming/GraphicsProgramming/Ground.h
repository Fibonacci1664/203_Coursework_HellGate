#pragma once
#include "Model.h"

class Ground
{
public:
	Ground();
	~Ground();

	void render();

	// GROUND MODEL FUNCS
	void initGround();
	void renderCobblePlane();

	// GROUND MODEL VARS
	Model* cobbleGround;
	char* cobbleGroundFilePath = "models/cobbleDecTri.obj";
	char* cobbleGroundTexPath = "gfx/textures/coobleGround.jpg";
};

