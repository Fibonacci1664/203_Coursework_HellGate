#pragma once
#include "CubeBI.h"

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

