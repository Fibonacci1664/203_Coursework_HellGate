#include "Crate.h"
#include <stdio.h>

Crate::Crate()
{
	initTextures();
}

Crate::~Crate()
{

}

void Crate::update(float dt)
{

}

void Crate::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	enableArrays();
	arrayDataArrangment();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubeBuildIndex);
	disableArrays();
	glDisable(GL_TEXTURE_2D);
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

void Crate::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Crate::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Crate::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
}