/*
 * About this class
 *		- Plank object made from:
 *			- A CubeBI (Build Index) object.
 *		- This class loads its own textures and draws itself calling its parent render
 *			this in turn uses glDrawElements(...).
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <stdio.h>
#include "CubeBI.h"

///////////////////////////////////////////////////////////////////////////////////////////

class Plank : public CubeBI
{
public:
	Plank();
	~Plank();

	void render();

protected:
	
private:
	void initTextures();

	GLuint m_texture;
	char* m_plankTexPath = "gfx/textures/oldWood_1.jpg";	
};

///////////////////////////////////////////////////////////////////////////////////////////