#include "SkySphere.h"
#include <stdio.h>

// Helps to get rid of seams on the texture.
constexpr auto GL_CLAMP_TO_EDGE = 0x812F;

SkySphere::SkySphere(float radius, float slices, float stacks)
{
	m_quadric = gluNewQuadric();
	initSkySphere(radius, slices, stacks);
	m_rotation = 0;
	m_speed = 0.5f;
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
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.				
	glRotatef(m_rotation, 0.5f, 0.5f, 0);
	glCallList(m_sphereList);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void SkySphere::initSkySphere(float radius, float slices, float stacks)
{
	initTextures(m_skySphereTexPath);

	m_sphereList = glGenLists(1);

	glNewList(m_sphereList, GL_COMPILE);
		gluSphere(m_quadric, radius, slices, stacks);		// Generate ONCE! call as many times as I like from render callList!
	glEndList();
}

void SkySphere::initTextures(char* filepath)
{
	// Mipmap generation does not happen as we don't want or need mipmaps for our skysphere.
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
	
	gluQuadricTexture(m_quadric, GLU_TRUE);									// Generate texture coords.
}
