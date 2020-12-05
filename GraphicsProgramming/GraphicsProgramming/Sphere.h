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
	Sphere(float radius, int slices, int stacks, char* filepath);
	~Sphere();

	void update(float dt);
	void render();
	void setWireFrameMode(bool isWireFrame);

protected:
	

private:
	void generateSphereVerts(float radius, int lats, int longs);
	void initSphere(float radius, int slices, int stacks, char* filepath);
	void initTextures(char* filepath);
	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

	bool m_wireFrame;
	const double PI = 3.14159265359;

	// TEXTURE VARS
	GLuint m_texture;
	
	// PROCEDURALLY GEN DATA
	std::vector<float> sphereVertices;
	std::vector<float> sphereNorms;
	std::vector<float> sphereTexCoords;
};