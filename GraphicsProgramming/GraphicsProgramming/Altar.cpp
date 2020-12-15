#include "Altar.h"
#include <stdio.h>


Altar::Altar()
{
	initTextures();
	initAltar();
}

Altar::~Altar()
{
	delete base;
	base = nullptr;

	delete top;
	top = nullptr;
}

void Altar::initAltar()
{
	base = new CubeBI();
	top = new CubeBI();
}

void Altar::render()
{
	glPushMatrix();
		glTranslatef(10.0f, 2.15f, 12.0f);
		glScalef(3.5f, 1.5f, 1.0f);
		base->render(m_baseTexture);

		glPushMatrix();
			glTranslatef(0, 1.1f, 0);
			glScalef(1.3f, 0.1f, 1.3f);

			// transform the base up.
			top->render(m_topTexture);
		glPopMatrix();
	glPopMatrix();
}

void Altar::initTextures()
{
	m_baseTexture = SOIL_load_OGL_texture
	(
		m_baseTexPath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Check for an error during the load process.
	if (m_baseTexture == 0)
	{
		printf("SOIL loading error altar base texture: '%s'\n", SOIL_last_result());
	}

	m_topTexture = SOIL_load_OGL_texture
	(
		m_topTexPath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Check for an error during the load process.
	if (m_topTexture == 0)
	{
		printf("SOIL loading error altar top texture: '%s'\n", SOIL_last_result());
	}
}