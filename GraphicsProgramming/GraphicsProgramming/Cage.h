/*
 * About this class
 *		- Cage object uses Vertex3f(...) to draw each face of a cuebe
 *		- There are 2 cubes drawn, one with the front face culled and
 *			the other with the back face culled. This ensure correctly
 *			drawn cages as the camera is roated around them.
 *		- This class loads its own textures and draws itself.
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

///////////////////////////////////////////////////////////////////////////////////////////

// This does not inherit from CubeBI as Plank and Crate do
// As this constructs the cubiod in a different manner, namely, vertex3f(...)

class Cage
{
public:
	Cage();
	~Cage();

	void update(float dt);
	void render(float scale);

private:
	void initTextures();
	void drawCage(float scale);

	GLuint m_texture;
	char* m_cageTexPath = "gfx/textures/rustyIronBars.png";
};

///////////////////////////////////////////////////////////////////////////////////////////