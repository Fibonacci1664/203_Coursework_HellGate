/*
 * About this class
 *		- Canlde object made from a procedurally generated:
 *			- Cylinder
 *			- Disc with extruded z-value.
 *		- This class loads its own textures and draws itself using glDrawArrays(...).
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
#include <vector>
#include "Disc.h"

///////////////////////////////////////////////////////////////////////////////////////////

class Candle
{
public:
	Candle(float resolution, float radius, float height);
	~Candle();

	void setWireFrameMode(bool isWireFrame);
	void render();

private:
	void initTextures();
	void initCandleTop(float resolution, float radius);
	void generateCylVerts(float resolution, float radius, float height);

	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

	GLuint m_texture;
	char* m_candleTexPath = "gfx/textures/candleWax.jpg";
	const float PI = 3.14159265359f;
	const float candleTopExtrusion = 0.1f;
	Disc* candleTop;
	float m_radius;
	float m_height;
	bool m_wireFrame;


	// CYLINDER
	std::vector<float> cylVerts;
	std::vector<float> cylNorms;
	std::vector<float> cylTexCoords;
};

///////////////////////////////////////////////////////////////////////////////////////////