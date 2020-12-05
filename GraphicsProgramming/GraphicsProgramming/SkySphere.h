#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"

class SkySphere
{
public:
	SkySphere(float radius, float slices, float stacks);
	~SkySphere();
	
	void update(float dt);
	void render();

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
