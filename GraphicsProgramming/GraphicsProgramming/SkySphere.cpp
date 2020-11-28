#include "SkySphere.h"
#include <stdio.h>

// Helps to get rid of seams on the texture.
constexpr auto GL_CLAMP_TO_EDGE = 0x812F;

SkySphere::SkySphere()
{
	m_quadric = gluNewQuadric();
	initSkySphere();
	m_rotation = 0;
	m_speed = 0.25;
	m_isSet = false;
}

SkySphere::~SkySphere()
{

}

void SkySphere::update(float dt)
{
	m_rotation += (m_speed * dt);
}

void SkySphere::render()
{
	glPushMatrix();		
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glRotatef(m_rotation, 0.5f, 0.5f, 0);
		renderSkySphere(1, 20, 20);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();	
}

void SkySphere::initSkySphere()
{
	m_skySpherePath = "gfx/skyspheres/starmap_8k.jpg";
	initTextures(m_skySpherePath);
}

void SkySphere::initTextures(char* filepath)
{
	// Mipmap generation does not happen as we don't want mipmaps for our skybox.
	m_texture = SOIL_load_OGL_texture
	(
		filepath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// Check for an error during the load process.
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	gluQuadricTexture(m_quadric, GLU_TRUE);									// Generate texture coords.
}

void SkySphere::renderSkySphere(float radius, float slices, float stacks)
{
	// This sets the initial orientation of the sphere so that the poles are above and below the viewer.
	// Without this the poles, upon initialisation are in front and behind the viewer.
	// Not that it matters too much as the night sky rotates anyway.
	/*if (!isSet)
	{
		glRotatef(90, 1.0f, 0, 0);
		isSet = true;
	}*/
	
	gluSphere(m_quadric, radius, slices, stacks);
}
