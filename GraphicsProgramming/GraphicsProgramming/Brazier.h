#pragma once
#include "Model.h"

class Brazier
{
public:
	Brazier();
	~Brazier();

	void render();

private:

	void initBrazier();

	Model* brazier;
	char* brazierFilePath = "models/brazier.obj";
	char* brazierTexPath = "gfx/textures/blackMetal.jpg";
};


