/*
 * About this class
 *		- Altar object consisting of two components
 *			- Base - CubeBI object
 *			- Top - CubeBI object
 *		- This class loads its own textures and draws itself.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CubeBI.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////

class Altar
{
public:
	Altar();
	~Altar();

	void render();

private:

	void initTextures();
	void initAltar();

	GLuint m_baseTexture;
	GLuint m_topTexture;
	char* m_baseTexPath = "gfx/textures/flowStone.jpg";
	char* m_topTexPath = "gfx/textures/darkStone.jpg";

	CubeBI* base;
	CubeBI* top;
};

///////////////////////////////////////////////////////////////////////////////////////////