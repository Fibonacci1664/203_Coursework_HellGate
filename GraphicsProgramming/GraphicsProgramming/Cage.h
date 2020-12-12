#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"

class Cage
{
public:
	Cage();
	~Cage();

	void update(float dt);
	void render(float scale);
	void drawCage(float scale);

private:
	void initTextures();

	GLuint m_texture;
	char* m_cageTexPath = "gfx/textures/rustyIronBars.png";
};