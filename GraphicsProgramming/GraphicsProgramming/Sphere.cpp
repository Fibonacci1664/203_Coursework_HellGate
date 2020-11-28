#include "Sphere.h"


// Constructor, maybe change this to render just a basic sphere then have separate func to call
// for setting things like translate, rotate, colour etc.
Sphere::Sphere()
{

}

// Destructor
Sphere::~Sphere()
{

}

// Make this func take colour and size params
void Sphere::renderSphere(float radius, float slices, float stacks)
{
	gluSphere(gluNewQuadric(), radius, slices, stacks);
}

