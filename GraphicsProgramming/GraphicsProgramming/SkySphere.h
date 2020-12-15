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

#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////

class SkySphere
{
public:
	SkySphere(float radius, float slices, float stacks);
	~SkySphere();
	
	void update(float dt);
	void render();
	void render2();

protected:

private:

	void initSkySphere(float radius, float slices, float stacks);
	void initTextures(char* filepath);

	GLuint m_sphereList;
	GLUquadric* m_quadric;

	float m_rotation;
	float m_speed;

	// TEXTURE VARS
	GLuint m_texture;
	char* m_skySphereTexPath = "gfx/skyspheres/starmap_8k.jpg";
};

///////////////////////////////////////////////////////////////////////////////////////////