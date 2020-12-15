#pragma once
#include "Model.h"

class RockyLand
{
public:

	RockyLand();
	~RockyLand();

	void render();

private:

	void initRockyLand();

	Model* rockyLand;
	char* rockyLandFilePath = "models/rocky_outcrop.obj";
	char* rockyLandTexPath = "gfx/textures/coobleGround.jpg";
};
