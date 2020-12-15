#pragma once
#include "Model.h"

class Skull
{
public:

	Skull();
	~Skull();

	void render();

private:

	void initSkull();

	Model* skull;
	char* skullFilePath = "models/skull_dec.obj";
	char* skullTexPath = "gfx/textures/skull_diffuse.jpg";
};

