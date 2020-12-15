/*
 * About this class
 *		- Page object which create ritual pages on the altar.
 *		- This object is rendered in immediate mode using glVertex3f(...).
 *		- This object loads its own textures and renders itself.
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

class Page
{
public:
	Page(float pageWidthX, float pageHeightZ, char* pageTexPath);
	~Page();

	void render();

private:
	void initTextures(char* pageTexPath);

	GLuint m_texture;
	float m_pageHeight;
	float m_pageWidth;
};

///////////////////////////////////////////////////////////////////////////////////////////