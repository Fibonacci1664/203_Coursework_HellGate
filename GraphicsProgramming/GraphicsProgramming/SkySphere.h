#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"

class SkySphere
{
public:
	SkySphere();
	~SkySphere();
	
	void update(float dt);
	void render();

	void renderSkySphere(float radius, float slices, float stacks);

protected:

private:

	void initSkySphere();
	void initTextures(char* filepath);

	GLuint m_texture;
	GLUquadric* m_quadric;

	float m_rotation;
	float m_speed;
	bool m_isSet;

	// TEXTURE VARS
	char* m_skySpherePath;
};

