#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"

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