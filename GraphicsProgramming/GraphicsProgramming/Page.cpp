/*
 * About this class
 *		- Page object which create ritual pages on the altar.
 *		- This object is rendered in immediate mode using glVertex3f(...).
 *		- This object loads its own textures and renders itself.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#include "Page.h"

///////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR.
Page::Page(float pageWidthX, float pageHeightZ, char* pageTexPath)
{
	initTextures(pageTexPath);
	m_pageHeight = pageHeightZ;
	m_pageWidth = pageWidthX;
}

// DESTRUCTOR.
Page::~Page()
{

}

///////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS.
void Page::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_QUADS);
		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(0, 0);
		glVertex3f(0.0f, 0.0f, 0.0f);

		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(0, 1.0f);
		glVertex3f(0.0f, 0.0f, m_pageHeight);

		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(m_pageWidth, 0.0f, m_pageHeight);

		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(1.0f, 0);
		glVertex3f(m_pageWidth, 0.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Page::initTextures(char* pageTexPath)
{
	m_texture = SOIL_load_OGL_texture
	(
		pageTexPath,
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

///////////////////////////////////////////////////////////////////////////////////////////