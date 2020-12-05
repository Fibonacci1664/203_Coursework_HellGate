#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <stdio.h>
#include <vector>

class Sphere
{
public:
	Sphere(float radius, float slices, float stacks);
	~Sphere();

	void update(float dt);
	void render();
	void setWireFrameMode(bool isWireFrame);

protected:
	

private:

	void setWireFrameMode();
	void generateSphereVerts(float radius, int lats, int longs);
	void initSphere(float radius, float slices, float stacks);
	void initTextures(char* filepath);
	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

	float m_rotation;
	float m_speed;
	bool m_wireFrame;
	const float PI = 3.14159265359;

	// TEXTURE VARS
	char* m_moonTexPath = "gfx/textures/4k_moon_fic.jpg";
	GLuint m_texture;
	
	// PROCEDURALLY GEN DATA
	std::vector<float> sphereVertices;
	std::vector<float> sphereNorms;
	std::vector<float> sphereTexCoords;
};