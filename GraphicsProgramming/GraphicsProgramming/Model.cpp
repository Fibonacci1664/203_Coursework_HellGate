// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// Helps to get rid of seams on the texture.
constexpr auto GL_CLAMP_TO_EDGE = 0x812F;

#include "Model.h"

Model::Model()
{
	m_isTextured = false;
	m_texture = 0;
}

Model::~Model()
{

}

bool Model::load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);

	if (!result)
	{
		MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	if (textureFilename != NULL)
	{
		m_isTextured = true;
		// Load the texture for this model.
		loadTexture(textureFilename);
	}

	return true;
}

void Model::render()
{	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	enableArrays();
	arrayDataArrangment();
	glDrawArrays(GL_TRIANGLES, 0, sortedVertex.size() / 3);
	disableArrays();
	glDisable(GL_TEXTURE_2D);
}


// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename)
{
	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;
	
	FILE* file = fopen(filename, "r");		// The 'r' means to read from the filename.

	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		// '%s' means read a string of characters until you hit whitespace,
		// in other words, read one word at a time.
		int res = fscanf(file, "%s", lineHeader);

		// If we hit the End of File, we're done.
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			/*	
			 *	    String compare, compare what we've extracted with the string "v", "vt", "vn", or "f".
			 *		Vertex, Texture coords, Norms, and Face respectively.
				<0	the first character that does not match has a lower value in ptr1 than in ptr2
				 0	the contents of both strings are equal
				>0	the first character that does not match has a greater value in ptr1 than in ptr2
			*/

			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);	// Look for 3 space seperated floats, and set the vertex values accordingly.
				verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);							// Look for 2 space seperated floats, and set the texture coord values accordingly.
				texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);	// Look for 3 space seperated floats, and set the normal values accordingly.
				norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];

				// Extract 9 decimal integers "%d" and stored them in the respective index positions 0 - 8.
																		//		v		t		  n
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",	&face[0], &face[1], &face[2],
																			&face[3], &face[4], &face[5],
																			&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}
				
				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}
			}
		}
	}

#pragma region unroll_data
	// "Unroll" the loaded obj information into a list of triangles.
	// By this point all model data has been read from the file, but is not in the correct order.
	// Loop over all the data and sort it into a render ready order/format.

	// Loop over all the faces.
	for (int i = 0; i < faces.size(); ++i)
	{
		// If our current 'i' value is a multiple of 3 then we're at vertex info/
		if (i % 3 == 0)
		{
			unsigned int indexPos = faces[i];	// retrieve the value stored at the face of the current iteration.

			float x = verts[indexPos - 1].x;	// Remeber to minus 1 for zero-based indexing.
			float y = verts[indexPos - 1].y;
			float z = verts[indexPos - 1].z;

			sortedVertex.push_back(x);
			sortedVertex.push_back(y);
			sortedVertex.push_back(z);
		}
		else if ((i - 1) % 3 == 0)			// If our current 'i' value - 1 is a multiple of 3, then we know we're 1 past vertex info, i.e. we're at tex coords.
		{
			// Store tex coords uv's.
			unsigned int indexPos = faces[i];

			float u = texCs[indexPos - 1].x;
			float v = texCs[indexPos - 1].y;

			sortedTexCoords.push_back(u);
			sortedTexCoords.push_back(v);
		}
		else								// Otherwise it's norms.
		{
			// Store norms xyz.
			unsigned int indexPos = faces[i];

			float x = norms[indexPos - 1].x;
			float y = norms[indexPos - 1].y;
			float z = norms[indexPos - 1].z;

			sortedNormals.push_back(x);
			sortedNormals.push_back(y);
			sortedNormals.push_back(z);
		}
	}

#pragma endregion unroll_data
		
	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();

	return true;
}
// END LOAD MODEL FUNCTION.

void Model::loadTexture(char* filename)
{
	m_texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

void Model::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Model::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Model::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, sortedVertex.data());
	glNormalPointer(GL_FLOAT, 0, sortedNormals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, sortedTexCoords.data());
}