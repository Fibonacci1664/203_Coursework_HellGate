/*
 * About this class
 *		- Skysphere object is created from a gluSphere using gluNewQuadric.
 *		- This is then passed into a call list to be used from render.
 *		- There are 2 seperate render functions depending on how you wish to render your skysphere:
 *			- Option 1, a unit radius sphere around the camera, (Gave me problems with stencil work!)
 *			- Option 2, a huge radius sphere that the entire world will live inside.
 *		- This class loads its own textures and draws itself.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

 ///////////////////////////////////////////////////////////////////////////////////////////

 // BEGIN REF
 /*
  * Helps to get rid of seams on the texture.
  *
  * Original @author - Dorbie, Feb 2006.
  *
  * Adapted from - https://community.khronos.org/t/skybox-with-seams/34441/5
  */
constexpr auto GL_CLAMP_TO_EDGE = 0x812F;
// END REF

#include "SkySphere.h"

///////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR.
SkySphere::SkySphere(float radius, float slices, float stacks, char* filepath)
{
	m_quadric = gluNewQuadric();
	initSkySphere(radius, slices, stacks, filepath);
	m_rotation = 0;
	m_speed = 0.5f;
}

// DESTRUCTOR.
SkySphere::~SkySphere()
{

}

///////////////////////////////////////////////////////////////////////////////////////////

// FUNCTIONS.
void SkySphere::update(float dt)
{
	m_rotation += (m_speed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////

void SkySphere::render2()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.				
	glRotatef(m_rotation, 0.5f, 0.5f, 0);
	glScalef(500.0f, 500.0f, 500.0f);			// Scale up the sky sphere to a 500 radius sphere. Far plane is set to 1000.
	glCallList(m_sphereList);
	glDisable(GL_TEXTURE_2D);
}

///////////////////////////////////////////////////////////////////////////////////////////

void SkySphere::initSkySphere(float radius, float slices, float stacks, char* filepath)
{
	initTextures(filepath);

	m_sphereList = glGenLists(1);

	glNewList(m_sphereList, GL_COMPILE);
		gluSphere(m_quadric, radius, slices, stacks);		// Generate ONCE! call as many times as I like from render callList!
	glEndList();
}

///////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////