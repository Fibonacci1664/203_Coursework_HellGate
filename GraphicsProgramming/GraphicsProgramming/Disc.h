#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <math.h>
#include <stdio.h>

class Disc
{
public:

	Disc(float resolution, float radius, char* texturePath, bool modifyZ, float zVal);
	~Disc();

	void render();
	void initTexture(char* texturePath);

	void generateDisc(float resolution, float radius);
	void generateDiscVerts(float resolution, float radius);
	void generateDiscNorms();
	void generateDiscTexCoords();

	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

	float discRadius;
	float numOfDiscVerts;
	bool m_modifyZValue;
	float m_zVal;
	const float PI = 3.14159265359f;
	const int MAX_DISC_RESOLUTION = 501; // This needs to be a multiple of three.
	const int X_Y_Z_VALUES = 3;
	const int U_V_VALUES = 2;


	// DISC
	float discVerts[501][3]{ {0} };
	float discNorms[501][3]{ {0} };
	float discTexCoords[501][2]{ {0} };

	GLuint m_texture;

private:

};
