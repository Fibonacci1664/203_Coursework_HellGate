#pragma once
#include "Model.h"

class Brazier
{
public:

	Brazier();
	~Brazier();

	void render();

	// GROUND MODEL FUNCS
	void initBrazier();

	// GROUND MODEL VARS
	Model* brazier;
	char* brazierFilePath = "models/brazier.obj";
	char* brazierTexPath = "gfx/textures/blackMetal.jpg";
};


