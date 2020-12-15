#include "Disc.h"

Disc::Disc(float resolution, float radius, char* texturePath, bool modifyZ, float zVal)
{
	m_modifyZValue = modifyZ;
	m_zVal = zVal;

	initTexture(texturePath);
	generateDisc(resolution, radius);
}

Disc::~Disc()
{

}

void Disc::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	enableArrays();
	arrayDataArrangment();
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)numOfDiscVerts);
	disableArrays();
	glDisable(GL_TEXTURE_2D);
}

void Disc::initTexture(char* texturePath)
{
	m_texture = SOIL_load_OGL_texture
	(
		texturePath,
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

void Disc::generateDisc(float resolution, float radius)
{
	generateDiscVerts(resolution, radius);
	generateDiscNorms();
	generateDiscTexCoords();
}

void Disc::generateDiscVerts(float resolution, float radius)
{
	// Set member variable to radius scale that has been passed in order that other funcs can know the radius.
	discRadius = radius;

	// We need a res of at least 3 or the interval calc is of no use
	// e.g. 2*PI/1(res) = 2 PI, so for this res(1) we would have 3 verts, a centre vert, a vert at (1,0,0) and then another 2PI round from that
	// i.e. in exactly the same place, this of course means we don't get a shape.
	// Kind of the same for res of 2, we have a centre vert and then alteranting for the next 5 verts between (1,0,0) and (-1,0,0) as we move
	// round in an interval of PI, again this does not result in any shape.
	// Also check that we don't pass in a resolution that would exceed that number of available indices in the array.
	if (resolution < 3 || (resolution * 3) > MAX_DISC_RESOLUTION)
	{
		return;
	}
	else
	{
		float interval = 2.0f * PI / resolution;
		float angle = 0.0f;
		// Segments wanted * number of positions, zero based indexing
		// e.g. res = 5, verts req = 15, this is 5 triangles each with 3 vertices, stored in an array 0 - 14.
		numOfDiscVerts = resolution * 3.0f;
		int count = 0;	// For counting verts in groups of 3 so we know when to increase angle.

		// Loop over each index pos(vertex position).
		for (int i = 0; i < numOfDiscVerts; ++i)
		{
			// At each vertex, set the corrosponding x,y,z values.
			for (int j = 0; j < 3; j++)
			{
				// If i is a multiple of 3 then we have stored 3 vertices already and so stored the starting pos again.
				if (i % 3 == 0)
				{
					discVerts[i][j] = 0;
				}
				else
				{
					// X Pos
					if (j == 0)
					{
						// All these various checks are to account for floating point math.
						// When the angle is at the values checked we clamp the value.
						if ((angle > 1.56 && angle < 1.58) || (angle > 4.71 && angle < 4.73))
						{
							discVerts[i][j] = 0;
						}
						else if (angle > 3.14 && angle < 3.2)
						{
							discVerts[i][j] = -radius;
						}
						else
						{
							discVerts[i][j] = radius * cos(angle);
						}
					}
					else if (j == 1) // Y Pos
					{
						if ((angle > 1.56 && angle < 1.58))
						{
							discVerts[i][j] = radius;
						}
						else if (angle > 4.71 && angle < 4.72)
						{
							discVerts[i][j] = -radius;
						}
						else if (angle > 3.14 && angle < 3.2)
						{
							discVerts[i][j] = 0;
						}
						else
						{
							discVerts[i][j] = radius * sin(angle);
						}
					}
					else // Z Pos
					{
						if (m_modifyZValue)
						{
							discVerts[i][j] = m_zVal;
						}
						else
						{
							discVerts[i][j] = 0;	// A 2D disc, store z = 0.
						}
					}
				}

				if (i >= 2)
				{
					++count;
				}
			}

			if (i == 1)
			{
				// increment angle
				angle += interval;
			}
			else if (i > 1 && count % 9 == 0)
			{
				// increment angle.
				angle += interval;

				if (angle > 6.28 && angle < 6.29)
				{
					angle = 0;
				}
			}
		}
	}
}

void Disc::generateDiscNorms()
{
	for (int i = 0; i < numOfDiscVerts; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == 2)
			{
				discNorms[i][j] = 1;
			}
			else
			{
				discNorms[i][j] = 0;
			}
		}
	}
}

void Disc::generateDiscTexCoords()
{
	// Loop over vertex array, retrieving x,y positional values
	// u = (cos(theta) / d) + 0.5;  this is the x pos at any given vertex
	// v = (sin(theta) / d) + 0.5;	this is the y pos at any given vertex

	float diameter = discRadius * 2;

	for (int i = 0; i < numOfDiscVerts; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == 2)
			{
				continue;
			}

			if (i % 3 == 0)
			{
				discTexCoords[i][j] = (discVerts[i][j] / diameter) + 0.5f;
			}
			else
			{
				if (j == 0)
				{
					discTexCoords[i][j] = (discVerts[i][j] / diameter) + 0.5f;
				}
				else
				{
					discTexCoords[i][j] = 0.5f - (discVerts[i][j] / diameter);
				}
			}
		}
	}
}

void Disc::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Disc::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Disc::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, discVerts);
	glNormalPointer(GL_FLOAT, 0, discNorms);
	glTexCoordPointer(2, GL_FLOAT, 0, discTexCoords);
}