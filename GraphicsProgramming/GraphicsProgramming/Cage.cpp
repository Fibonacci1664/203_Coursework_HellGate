#include "Cage.h"
#include <stdio.h>

Cage::Cage()
{
	initTextures();
}

Cage::~Cage()
{

}

void Cage::update(float dt)
{

}

void Cage::render(float scale)
{
	// Rendering a cage culling front face.
	glPushMatrix();
		glEnable(GL_BLEND);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glEnable(GL_TEXTURE_2D);
		drawCage(scale);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	glPopMatrix();

	// Rendering another cage culling back face.
	glPushMatrix();
		glEnable(GL_BLEND);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_2D);
		drawCage(scale);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	glPopMatrix();
}

void Cage::drawCage(float scale)
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBegin(GL_QUADS);

		// BACK FACE
		glNormal3f(0, 0, -1.0f);
		glTexCoord2f(0, 0);
		glVertex3f(scale, scale, -scale);		// Vertex F
		glNormal3f(0, 0, -1.0f);
		glTexCoord2f(0, 1.0f);
		glVertex3f(scale, -scale, -scale);		// Vertex E
		glNormal3f(0, 0, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-scale, -scale, -scale);	// Vertex G
		glNormal3f(0, 0, -1.0f);
		glTexCoord2f(1.0f, 0);
		glVertex3f(-scale, scale, -scale);		// Vertex H

		// RHS FACE
		glNormal3f(1.0f, 0, 0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(scale, -scale, -scale);		// Vertex E
		glNormal3f(1.0f, 0, 0);
		glTexCoord2f(1.0f, 0);
		glVertex3f(scale, scale, -scale);		// Vertex F
		glNormal3f(1.0f, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(scale, scale, scale);		// Vertex D
		glNormal3f(1.0f, 0, 0);
		glTexCoord2f(0, 1.0f);
		glVertex3f(scale, -scale, scale);		// Vertex C

		// LHS FACE
		glNormal3f(-1.0f, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(-scale, scale, -scale);		// Vertex H
		glNormal3f(-1.0f, 0, 0);
		glTexCoord2f(0, 1.0f);
		glVertex3f(-scale, -scale, -scale);	// Vertex G
		glNormal3f(-1.0f, 0, 0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-scale, -scale, scale);		// Vertex B
		glNormal3f(-1.0f, 0, 0);
		glTexCoord2f(1.0f, 0);
		glVertex3f(-scale, scale, scale);		// Veretx A

		// TOP FACE
		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(0, 0);
		glVertex3f(-scale, scale, scale);		// Veretx A
		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(0, 1.0f);
		glVertex3f(scale, scale, scale);		// Vertex D
		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(scale, scale, -scale);		// Vertex F
		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(1.0f, 0);
		glVertex3f(-scale, scale, -scale);		// Vertex H

		//// BTM FACE
		//glNormal3f(0, -1.0f, 0);
		//glTexCoord2f(0, 0);
		//glVertex3f(-scale, -scale, scale);		// Vertex B
		//glNormal3f(0, -1.0f, 0);
		//glTexCoord2f(0, 1.0f);
		//glVertex3f(scale, -scale, scale);		// Vertex C
		//glNormal3f(0, -1.0f, 0);
		//glTexCoord2f(1.0f, 1.0f);
		//glVertex3f(scale, -scale, -scale);		// Vertex E
		//glNormal3f(0, -1.0f, 0);
		//glTexCoord2f(1.0f, 0);
		//glVertex3f(-scale, -scale, -scale);	// Vertex G

		// FRONT FACE
		glNormal3f(0, 0, 1.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-scale, scale, scale);		// Veretx A
		glNormal3f(0, 0, 1.0f);
		glTexCoord2f(0, 1.0f);
		glVertex3f(-scale, -scale, scale);		// Vertex B
		glNormal3f(0, 0, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(scale, -scale, scale);		// Vertex C
		glNormal3f(0, 0, 1.0f);
		glTexCoord2f(1.0f, 0);
		glVertex3f(scale, scale, scale);		// Vertex D

	glEnd();
}

void Cage::initTextures()
{
	m_texture = SOIL_load_OGL_texture
	(
		m_cageTexPath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// Check for an error during the load process.
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}