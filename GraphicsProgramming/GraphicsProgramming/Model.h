// Model class, represents a loaded OBJ model
// handles the loading/processing of the model file. Also loads and stores its own texture
// NOT complete, for students to complete. Model data requires being sorted and the render function needs completed.
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