/*
 * About this class
 *		- Crate object made from:
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
#include "CubeBI.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////

class Crate : public CubeBI
{
public:
	Crate();
	~Crate();

	void render();

private:
	void initTextures();

	GLuint m_texture;
	char* m_crateTexPath = "gfx/textures/oldCrate.png";
};

///////////////////////////////////////////////////////////////////////////////////////////