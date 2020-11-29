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
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.				
		glRotatef(m_rotation, 0.5f, 0.5f, 0);
		glCallList(m_sphereList);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();	
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
	
	gluQuadricTexture(m_quadric, GLU_TRUE);									// Generate texture coords.
}

//void SkySphere::initSkySphere(float radius, float slices, float stacks)
//{
//	// This sets the initial orientation of the sphere so that the poles are above and below the viewer.
//	// Without this the poles, upon initialisation are in front and behind the viewer.
//	// Not that it matters too much as the night sky rotates anyway.
//	/*if (!isSet)
//	{
//		glRotatef(90, 1.0f, 0, 0);
//		isSet = true;
//	}*/
//
//	//listName = glGenLists(1);
//	//glNewList(listName, GL_COMPILE);
//	//glColor3f(1.0, 0.0, 0.0);  /*  current color red  */
//	//glBegin(GL_TRIANGLES);
//	//glVertex2f(0.0, 0.0);
//	//glVertex2f(1.0, 0.0);
//	//glVertex2f(0.0, 1.0);
//	//glEnd();
//	//glTranslatef(1.5, 0.0, 0.0); /*  move position  */
//	//glEndList();
//	//glShadeModel(GL_FLAT);
//
//	
//}
