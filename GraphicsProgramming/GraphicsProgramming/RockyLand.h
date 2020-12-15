/*
 * About this class
 *		- Rocky Land object is a loaded model
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

//////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Model.h"

//////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////