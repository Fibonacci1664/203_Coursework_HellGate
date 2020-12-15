#include "Candle.h"

// Helps to get rid of seams on the texture.
constexpr auto GL_CLAMP_TO_EDGE = 0x812F;

// Constructor, maybe change this to render just a basic sphere then have separate func to call
// for setting things like translate, rotate, colour etc.
Candle::Candle(float resolution, float radius, float height)
{
	m_radius = radius;
	m_height = height;	
	initTextures();
	initCandleTop(resolution, radius);
	generateCylVerts(resolution, radius, height);
	m_wireFrame = false;
}

// Destructor
Candle::~Candle()
{
	delete candleTop;
	candleTop = nullptr;
}

void Candle::render()
{
	glPushMatrix();		
		glTranslatef(0.0f, m_height + candleTopExtrusion, -m_radius + candleTopExtrusion);
		glRotatef(90.0f, 1.0f, 0, 0);
		candleTop->render();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
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

	glDrawArrays(GL_QUADS, 0, cylVerts.size() / 3);
	glDisable(GL_CULL_FACE);
	disableArrays();
	glDisable(GL_TEXTURE_2D);
}

void Candle::setWireFrameMode(bool isWireFrame)
{
	m_wireFrame = isWireFrame;
}

void Candle::initTextures()
{
	m_texture = SOIL_load_OGL_texture
	(
		m_candleTexPath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Check for an error during the load process.
	if (m_texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}

void Candle::initCandleTop(float resolution, float radius)
{
	candleTop = new Disc(resolution, radius, m_candleTexPath, true, candleTopExtrusion);
}

void Candle::generateCylVerts(float resolution, float radius, float height)
{
	float angleInterval = 2.0f * PI / resolution;
	float uTexInterval = 1.0f / resolution;
	float vTexInterval = 1.0f / height;
	float angle = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	float u = 0;
	float v = 0;

	// Loop for the amount of height req. STACKS
	for (float i = 0; i < height; ++i)
	{
		// Loop for the amount of resolution req. SEGMENTS
		for (float j = 0; j < resolution; ++j)
		{
			// Build quads.
			// Vertex 1.
			x = radius * sinf(angle);
			y = i;
			z = radius * cosf(angle);

			cylVerts.push_back(x);
			cylVerts.push_back(y);
			cylVerts.push_back(z);
			cylNorms.push_back(x / radius);
			cylNorms.push_back(0);
			cylNorms.push_back(z / radius);
			cylTexCoords.push_back(u);
			cylTexCoords.push_back(v);

			float temp = i + 1;
			float tempV = v + vTexInterval;

			// Vert 2.
			x = radius * sinf(angle);
			y = temp;
			z = radius * cosf(angle);

			cylVerts.push_back(x);
			cylVerts.push_back(y);
			cylVerts.push_back(z);
			cylNorms.push_back(x / radius);
			cylNorms.push_back(0);
			cylNorms.push_back(z / radius);
			cylTexCoords.push_back(u);
			cylTexCoords.push_back(tempV);

			float tempAngle = angle + angleInterval;
			float tempU = u + uTexInterval;

			// Vert 3.
			x = radius * sinf(tempAngle);
			y = temp;
			z = radius * cosf(tempAngle);

			cylVerts.push_back(x);
			cylVerts.push_back(y);
			cylVerts.push_back(z);
			cylNorms.push_back(x / radius);
			cylNorms.push_back(0);
			cylNorms.push_back(z / radius);
			cylTexCoords.push_back(tempU);
			cylTexCoords.push_back(tempV);

			// Vert 4.
			x = radius * sinf(tempAngle);
			y = i;
			z = radius * cosf(tempAngle);

			cylVerts.push_back(x);
			cylVerts.push_back(y);
			cylVerts.push_back(z);
			cylNorms.push_back(x / radius);
			cylNorms.push_back(0);
			cylNorms.push_back(z / radius);
			cylTexCoords.push_back(tempU);
			cylTexCoords.push_back(v);

			angle += angleInterval;
			u += uTexInterval;
		}

		v += vTexInterval;
		u = 0;
	}
}

void Candle::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Candle::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Candle::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, cylVerts.data());
	glNormalPointer(GL_FLOAT, 0, cylNorms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, cylTexCoords.data());
}