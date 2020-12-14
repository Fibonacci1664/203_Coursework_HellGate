#pragma once
#include "Model.h"

class RockyLand
{
public:

	RockyLand();
	~RockyLand();

	void render();

	// GROUND MODEL FUNCS
	void initRockyLand();

	// GROUND MODEL VARS
	Model* rockyLand;
	char* rockyLandFilePath = "models/rocky_outcrop.obj";
	char* rockyLandTexPath = "gfx/textures/coobleGround.jpg";
};
