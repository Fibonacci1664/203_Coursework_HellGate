/*
 * About this class
 *		- Parent object for anything cubiod which uses a build index to draw itself.
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

///////////////////////////////////////////////////////////////////////////////////////////

class CubeBI
{
public:
	CubeBI();
	~CubeBI();

	void render(GLuint texture);

private:
	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

	// USE THIS FOR RENDER METHODS.
	float verts[72] = { -1.0,	-1.0,	1.0,		// Vertex #0
						1.0,	1.0,	1.0,		// Vertex #1
						-1.0,	1.0,	1.0,		// Vertex #2
						1.0,	-1.0,	1.0,		// Vertex #3
						1.0,	-1.0,	1.0,		// Vertex #4
						1.0,	1.0,	-1.0,		// Vertex #5
						1.0,	1.0,	1.0,		// Vertex #6
						1.0,	-1.0,	-1.0,		// Vertex #7
						1.0,	-1.0,	-1.0,		// Vertex #8
						-1.0,	1.0,	-1.0,		// Vertex #9
						1.0,	1.0,	-1.0,		// Vertex #10
						-1.0,	-1.0,	-1.0,		// Vertex #11
						-1.0,	-1.0,	-1.0,		// Vertex #12
						-1.0,	1.0,	1.0,		// Vertex #13
						-1.0,	1.0,	-1.0,		// Vertex #14
						-1.0,	-1.0,	1.0,		// Vertex #15
						-1.0,	1.0,	1.0,		// Vertex #16
						1.0,	1.0,	-1.0,		// Vertex #17
						-1.0,	1.0,	-1.0,		// Vertex #18
						1.0,	1.0,	1.0,		// Vertex #19
						-1.0,	-1.0,	1.0,		// Vertex #20
						1.0,	-1.0,	-1.0,		// Vertex #21
						-1.0,	-1.0,	-1.0,		// Vertex #22
						1.0,	-1.0,	1.0,		// Vertex #23
	};

	float norms[12] = { 0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
	};

	// MAP ONLY 4 TEXT COORDS IF USING METHODS 1 OR 3, THIS NEEDS TO MATCH THE INDEX ORDER IN THE ARRAY AND HAVE THE SAME AMOUNT OF VERTS
	float texcoords[48] = {	// FRONT
							0.0, 1.0, 		//0
							1.0, 0.0, 		//1
							0.0, 0.0, 		//2
							1.0, 1.0, 		//3
							// RIGHT
							0.0, 1.0, 		//4
							1.0, 0.0, 		//5
							0.0, 0.0, 		//6
							1.0, 1.0, 		//7
							// BACK
							0.0, 1.0, 		//8
							1.0, 0.0, 		//9
							0.0, 0.0, 		//10
							1.0, 1.0, 		//11
							// LEFT
							0.0, 1.0, 		//12
							1.0, 0.0, 		//13
							0.0, 0.0, 		//14
							1.0, 1.0, 		//15
							// TOP
							0.0, 1.0, 		//16
							1.0, 0.0, 		//17
							0.0, 0.0, 		//18
							1.0, 1.0, 		//19
							// BTM
							0.0, 1.0, 		//20
							1.0, 0.0, 		//21
							0.0, 0.0, 		//22
							1.0, 1.0, 		//23
	};

	GLubyte cubeBuildIndex[36] = { 0, 1, 2, 0, 3, 1,			// Front
									4, 5, 6, 4, 7, 5,			// Right
									8, 9, 10, 8, 11, 9,			// Back
									12, 13, 14, 12, 15, 13,		// Left
									16, 17, 18, 16, 19, 17,		// Top
									20, 21, 22, 20, 23, 21		// Btm
	};
};

///////////////////////////////////////////////////////////////////////////////////////////