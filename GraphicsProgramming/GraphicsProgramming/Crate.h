#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include "CubeBI.h"

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