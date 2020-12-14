#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SOIL.h"
#include <math.h>
#include <stdio.h>

constexpr int MAX_DISC_RESOLUTION = 501; // This needs to be a multiple of three.
constexpr int X_Y_Z_VALUES = 3;
constexpr int U_V_VALUES = 2;
const float PI = 3.14159265359f;

class Coin
{
public:

	Coin(int resolution, float radius);
	~Coin();


	void render();
	void initTexture();

	void generateDisc(int resolution, float radius);
	void generateDiscVerts(int resolution, float radius);
	void generateDiscNorms();
	void generateDiscTexCoords();

	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

	float discRadius;
	int numOfDiscVerts;

	// DISC
	float discVerts[MAX_DISC_RESOLUTION][X_Y_Z_VALUES]{ {0} };
	float discNorms[MAX_DISC_RESOLUTION][X_Y_Z_VALUES]{ {0} };
	float discTexCoords[MAX_DISC_RESOLUTION][U_V_VALUES]{ {0} };

	GLuint m_texture;
	char* m_wheelTexPath = "gfx/textures/goldCoin.png";

private:

};

