#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include "SOIL.h"
#include <vector>

constexpr int MAX_DISC_RESOLUTION = 501; // This needs to be a multiple of three.
constexpr int MAX_SPHERE_RESOLUTION = 15000;
constexpr int X_Y_Z_VALUES = 3;
constexpr int U_V_VALUES = 2;
const float PI = 3.14159265359f;

class Shape
{
	public:
		Shape();
		Shape(const char* filepath);
		~Shape();

		void initTexture(const char* filepath);

		void render1();
		void render2();
		void render3(int numOfIndices);
		void renderDisc();

		void generateDiscVerts(int resolution, float radius);
		void generateDiscNorms();
		void generateDiscTexCoords();
		void generateSphereVerts(float radius, int lats, int longs);
		void generateCylVerts(int resolution, float radius, float height);

		void enableArrays();
		void disableArrays();
		void arrayDataArrangment();
		void discArrayDataArrangment();

		float discRadius;
		int numOfDiscVerts;
		int numOfSphereVerts;
		bool isTextured;
		GLuint texture;
		bool copied = false;
		
		// DISC
		float discVerts[MAX_DISC_RESOLUTION][X_Y_Z_VALUES]{ {0} };
		float discNorms[MAX_DISC_RESOLUTION][X_Y_Z_VALUES]{ {0} };
		float discTexCoords[MAX_DISC_RESOLUTION][U_V_VALUES]{ {0} };

		// SHPERE
		float sphereVerts[MAX_SPHERE_RESOLUTION]{ 0 };
		std::vector<float> sphereVertices;
		std::vector<float> sphereNorms;
		std::vector<float> sphereTexCoords;

		// CYLINDER
		std::vector<float> cylVerts;
		std::vector<float> cylNorms;
		std::vector<float> cylTexCoords;
};
#endif 
