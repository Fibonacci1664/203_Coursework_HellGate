/*
 * About this class
 *		- Ground object is a loaded model.
 *		- Renders a plane of ground procedurally.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Model.h"

///////////////////////////////////////////////////////////////////////////////////////////

class Ground
{
public:
	Ground();
	~Ground();

	void render();

private:

	void initGround();
	void renderCobblePlane();

	Model* cobbleGround;
	char* cobbleGroundFilePath = "models/cobbleDecTri.obj";
	char* cobbleGroundTexPath = "gfx/textures/coobleGround.jpg";
};

///////////////////////////////////////////////////////////////////////////////////////////