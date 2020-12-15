/*
 * About this class
 *		- Handles all things Model related, namely:
 *			- Loading model data (.obj).
 *			- Parsing model data (tris).
 *			- Storing model data in new data structures.
 *			- Loading textures (NOT .mtl files).
 *			- Rendering model using glDrawArrays(...).
 *
 * Original @author Mark Ropper / Paul Robertson
 *
 * Updated by @author D. Green.
 *
 * © D. Green. 2020.
 */

 ///////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MODEL_H_
#define _MODEL_H_

// INCLUDES //
#include <glut.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>

using namespace std;

// MY CLASS INCLUDES //
#include <vector>
#include "Vector3.h"
#include "SOIL.h"

///////////////////////////////////////////////////////////////////////////////////////////

class Model
{

public:

	Model();
	~Model();

	bool load(char* modelFilename, char* textureFilename);
	void render();

	void enableArrays();
	void disableArrays();
	void arrayDataArrangment();

private:

	void loadTexture(char*);
	bool loadModel(char*);

	// model texture
	GLuint m_texture;

	// Storage for sorted data
	vector<float> sortedVertex, sortedNormals, sortedTexCoords;
	
	bool m_isTextured;
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////