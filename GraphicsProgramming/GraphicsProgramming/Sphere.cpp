#include "Sphere.h"

// Helps to get rid of seams on the texture.
constexpr auto GL_CLAMP_TO_EDGE = 0x812F;

// Constructor, maybe change this to render just a basic sphere then have separate func to call
// for setting things like translate, rotate, colour etc.
Sphere::Sphere(float radius, int slices, int stacks, char* filepath)
{
	initSphere(radius, slices, stacks, filepath);
	m_wireFrame = false;
}

// Destructor
Sphere::~Sphere()
{
	
}

void Sphere::render()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// Takes care of horrible seams on the texture mapping.	
	enableArrays();
	arrayDataArrangment();

	if (m_wireFrame)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	glDrawArrays(GL_QUADS, 0, sphereVertices.size() / 3);
	glDisable(GL_CULL_FACE);
	disableArrays();
	glDisable(GL_TEXTURE_2D);
}

void Sphere::setWireFrameMode(bool isWireFrame)
{
	m_wireFrame = isWireFrame;
}

void Sphere::initSphere(float radius, int slices, int stacks, char* filepath)
{
	initTextures(filepath);
	generateSphereVerts(radius, slices, stacks);
}

void Sphere::initTextures(char* filepath)
{
	m_texture = SOIL_load_OGL_texture
	(
		filepath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// Check for an error during the load process.
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

void Sphere::generateSphereVerts(float radius, int lats, int longs)
{
	float thetaInterval = 2.0f * PI / longs;			// longitude(verticals)
	float deltaInterval = PI / lats;					// latitude(horizontals)
	float uTexInterval = 1.0f / longs;
	float vTexInterval = 1.0f / lats;
	float theta = 0;
	float delta = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	float u = 0;
	float v = 0;

	// Loop for the amount of lats req. (horizontals) STACKS
	for (int i = 0; i < lats; ++i)
	{
		// Loop for the amount of longs req. (verticals) SEGMENTS
		for (int j = 0; j < longs; ++j)
		{
			// Build quads.
			// Vertex 1.
			x = radius * cosf(theta) * sinf(delta);
			y = radius * cosf(delta);
			z = radius * sinf(theta) * sinf(delta);

			sphereVertices.push_back(x);
			sphereVertices.push_back(y);
			sphereVertices.push_back(z);
			sphereNorms.push_back(x / radius);
			sphereNorms.push_back(y / radius);
			sphereNorms.push_back(z / radius);
			sphereTexCoords.push_back(u);
			sphereTexCoords.push_back(v);

			///////////////////////////////////////////////////////////////////////////////////////

			// Temp increase delta to move "down" the sphere
			float tempDelta = delta + deltaInterval;
			float tempV = v + vTexInterval;

			// Vertex 2 update xyz
			x = radius * cosf(theta) * sinf(tempDelta);
			y = radius * cosf(tempDelta);
			z = radius * sinf(theta) * sinf(tempDelta);

			// pushback xyz
			sphereVertices.push_back(x);
			sphereVertices.push_back(y);
			sphereVertices.push_back(z);
			sphereNorms.push_back(x / radius);
			sphereNorms.push_back(y / radius);
			sphereNorms.push_back(z / radius);
			sphereTexCoords.push_back(u);
			sphereTexCoords.push_back(tempV);

			///////////////////////////////////////////////////////////////////////////////////////

			// Temp increase theta to move "around" the sphere.
			float tempTheta = theta + thetaInterval;
			float tempU = u + uTexInterval;

			// Vertex 3 update xyz
			x = radius * cosf(tempTheta) * sinf(tempDelta);
			y = radius * cosf(tempDelta);
			z = radius * sinf(tempTheta) * sinf(tempDelta);

			// pushback xyz
			sphereVertices.push_back(x);
			sphereVertices.push_back(y);
			sphereVertices.push_back(z);
			sphereNorms.push_back(x / radius);
			sphereNorms.push_back(y / radius);
			sphereNorms.push_back(z / radius);
			sphereTexCoords.push_back(tempU);
			sphereTexCoords.push_back(tempV);

			///////////////////////////////////////////////////////////////////////////////////////

			// Vertex 4 update xyz
			x = radius * cosf(tempTheta) * sinf(delta);
			y = radius * cosf(delta);
			z = radius * sinf(tempTheta) * sinf(delta);

			// pushback xyz
			sphereVertices.push_back(x);
			sphereVertices.push_back(y);
			sphereVertices.push_back(z);
			sphereNorms.push_back(x / radius);
			sphereNorms.push_back(y / radius);
			sphereNorms.push_back(z / radius);
			sphereTexCoords.push_back(tempU);
			sphereTexCoords.push_back(v);

			// Permenantly increase theta to move "down" a layer.
			theta += thetaInterval;
			u += uTexInterval;
		}

		// Permenantly increase delta to move "around" to next sphere "segment"
		delta += deltaInterval;
		v += vTexInterval;
		u = 0;
	}
}

void Sphere::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Sphere::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Sphere::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, sphereVertices.data());
	glNormalPointer(GL_FLOAT, 0, sphereNorms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, sphereTexCoords.data());
}