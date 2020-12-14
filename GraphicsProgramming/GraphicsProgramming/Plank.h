#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include "CubeBI.h"

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

