#include "Crate.h"
#include <stdio.h>

Crate::Crate()
{
	initTextures();
}

Crate::~Crate()
{

}

void Crate::render()
{
	CubeBI::render(m_texture);
}

void Crate::initTextures()
{
	m_texture = SOIL_load_OGL_texture
	(
		m_crateTexPath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// Check for an error during the load process.
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}