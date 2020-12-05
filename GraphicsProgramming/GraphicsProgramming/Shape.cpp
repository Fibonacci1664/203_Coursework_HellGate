#include "shape.h"
#include<iostream>

// USE THIS FOR RENDER 1 & 3 METHODS.
extern float verts[] = {	-1.0,	-1.0,	1.0,		// Vertex #0
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

// USE THIS FOR RENDER 2 GL_TRIANGLES, METHOD 2 WILL BUILD SHAPE IN THE ORDER THE ARRAY IS
// SO THE ARRAY MUST BE IN THE CORRECT BUILD ORDER!
							// TRI 1
//extern float verts[] = {   -1.0, -1.0, 1.0,			// Vertex #1
//							1.0,  1.0, 1.0,			// Vertex #3
//							-1.0,  1.0, 1.0,		// Vertex #0	
//							
//							// TRI 2
//						   -1.0, -1.0, 1.0,			// Vertex #1
//							1.0, -1.0, 1.0,			// Vertex #2
//							1.0,  1.0, 1.0,			// Vertex #3
//						   
//};

extern float norms[] = {	0.0, 0.0, 1.0,		//0
							0.0, 0.0, 1.0,		//1
 							0.0, 0.0, 1.0,		//2
							0.0, 0.0, 1.0,		//3
							};		

// YOU NEED TO MAP 6 TEXT COORDS IF USING METHOD 2, THAT IS THIS VERISON BELOW.
//extern float texcoords[] = {	0.0, 1.0, 		//1
//								1.0, 0.0, 		//3
// 								0.0, 0.0, 		//0
//
//								0.0, 1.0, 		//1
//								1.0, 1.0, 		//2
//								1.0, 0.0, 		//3
//								};

// MAP ONLY 4 TEXT COORDS IF USING METHODS 1 OR 3, THIS NEEDS TO MATCH THE INDEX ORDER IN THE ARRAY AND HAVE THE SAME AMOUNT OF VERTS
extern float texcoords[] = {	// FRONT
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

// Test build index I was using for creating quads.
//extern GLubyte buildIndex[] = { 1, 3, 0, 1, 2, 3 };

extern GLubyte cubeBuildIndex[] = { 0, 1, 2, 0, 3, 1,			// Front
									4, 5, 6, 4, 7, 5,			// Right
									8, 9, 10, 8, 11, 9,			// Back
									12, 13, 14, 12, 15, 13,		// Left
									16, 17, 18, 16, 19, 17,		// Top
									20, 21, 22, 20, 23, 21 };	// Btm



// Default untextured shape.
Shape::Shape()
{
	isTextured = false;
	texture = 0;
}

// Textured shape. Takes the filepath of the location of the wanted texture.
Shape::Shape(const char* filepath)
{
	isTextured = true;
	initTexture(filepath);
}

Shape::~Shape()
{

}

void Shape::initTexture(const char* filepath)
{
	texture = SOIL_load_OGL_texture(filepath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Shape::render1()
{
	// add code to render the cube (above) using method 1
	// USING QUADS.
	/*enableArrays();
	arrayDataArrangment();
	glBegin(GL_QUADS);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
	glEnd();
	disableArrays();*/

	// USING TRIANGLES
	if (isTextured)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	enableArrays();
	arrayDataArrangment();
	glBegin(GL_TRIANGLES);
		glArrayElement(1);
		glArrayElement(3);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);
	glEnd();
	disableArrays();
}

void Shape::render2()
{
	// add code to render the cube (above) using method 2
	// USING QUADS
	/*enableArrays();
	arrayDataArrangment();
	glDrawArrays(GL_QUADS, 0, 4);
	disableArrays();*/

	// USING TRIANGLES
	if (isTextured)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	enableArrays();
	arrayDataArrangment();
	glDrawArrays(GL_QUADS, 0, cylVerts.size()/3);
	disableArrays();
}

void Shape::renderDisc()
{
	// add code to render the cube (above) using method 2
	// USING QUADS
	/*enableArrays();
	arrayDataArrangment();
	glDrawArrays(GL_QUADS, 0, 4);
	disableArrays();*/

	// USING TRIANGLES
	if (isTextured)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	enableArrays();
	discArrayDataArrangment();
	glDrawArrays(GL_TRIANGLES, 0, numOfDiscVerts);
	disableArrays();
}

void Shape::render3(int numOfIndices)
{
	// add code to render the cube (above) using method 3
	if (isTextured)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	enableArrays();
	arrayDataArrangment();
	glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_BYTE, cubeBuildIndex);
	disableArrays();
}

void Shape::generateCylVerts(int resolution, float radius, float height)
{
	float angleInterval = 2 * PI / resolution;
	float uTexInterval = 1.0f / resolution;
	float vTexInterval = 1.0f / height;
	float angle = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	float u = 0;
	float v = 0;

	// Loop for the amount of height req. STACKS
	for (int i = 0; i < height; ++i)
	{
		// Loop for the amount of resolution req. SEGMENTS
		for (int j = 0; j < resolution; ++j)
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

void Shape::generateDiscVerts(int resolution, float radius)
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
		float interval = 2 * PI / resolution;
		float angle = 0;
		// Segments wanted * number of positions, zero based indexing
		// e.g. res = 5, verts req = 15, this is 5 triangles each with 3 vertices, stored in an array 0 - 14.
		numOfDiscVerts = resolution  * 3;
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
						discVerts[i][j] = 0;	// A 2D disc, store z = 0.
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

void Shape::generateDiscNorms()
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

void Shape::generateDiscTexCoords()
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

void Shape::generateSphereVerts(float radius, int lats, int longs)
{
	float thetaInterval = 2.0f * PI / longs;			// longitude(verticals)
	float deltaInterval =  PI / lats;					// latitude(horizontals)
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

void Shape::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, cylVerts.data());
	glNormalPointer(GL_FLOAT, 0, cylNorms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, cylTexCoords.data());
}

void Shape::discArrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, discVerts);
	glNormalPointer(GL_FLOAT, 0, discNorms);
	glTexCoordPointer(2, GL_FLOAT, 0, discTexCoords);
}
