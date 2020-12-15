#include "Plank.h"
#include <stdio.h>

Plank::Plank()
{
	initTextures();
}

Plank::~Plank()
{

}

void Plank::render()
{
	CubeBI::render(m_texture);
}

void Plank::initTextures()
{
	m_texture = SOIL_load_OGL_texture
	(
		m_plankTexPath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Check for an error during the load process.
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}