#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <stdio.h>

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

