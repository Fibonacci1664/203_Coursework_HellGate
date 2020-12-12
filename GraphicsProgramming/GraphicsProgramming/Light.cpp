#include "Light.h"

Light::Light()
{

}

Light::~Light()
{

}

void Light::renderDirectionalLight(GLenum lightNum, GLfloat diffuse[], GLfloat position[])
{
	glLightfv(lightNum, GL_DIFFUSE, diffuse);
	glLightfv(lightNum, GL_POSITION, position);
	glEnable(lightNum);
}


void Light::renderPointLight(GLenum lightNum, GLfloat ambience[], GLfloat diffuse[], GLfloat position[])
{
	glLightfv(lightNum, GL_AMBIENT, ambience);
	glLightfv(lightNum, GL_DIFFUSE, diffuse);
	glLightfv(lightNum, GL_POSITION, position);
	glEnable(lightNum);
}

void Light::renderSpotLight(GLenum lightNum, GLfloat ambience[], GLfloat diffuse[], GLfloat position[], GLfloat spot_dir[])
{
	glLightfv(lightNum, GL_AMBIENT, ambience);
	glLightfv(lightNum, GL_DIFFUSE, diffuse);
	glLightfv(lightNum, GL_POSITION, position);
	glLightf(lightNum, GL_SPOT_CUTOFF, 25.0f);
	glLightfv(lightNum, GL_SPOT_DIRECTION, spot_dir);
	glLightf(lightNum, GL_SPOT_EXPONENT, 100.0f);
	glEnable(lightNum);
}

void Light::renderSpecularLight(GLenum lightNum, GLfloat ambience[], GLfloat diffuse[], GLfloat position[], GLfloat specular[])
{
	glLightfv(lightNum, GL_AMBIENT, ambience);
	glLightfv(lightNum, GL_DIFFUSE, diffuse);
	glLightfv(lightNum, GL_POSITION, position);
	glLightfv(lightNum, GL_SPECULAR, specular);
	glEnable(lightNum);
}

void Light::setAttenuation(GLenum lightNum, GLfloat constantVal, GLfloat linearVal, GLfloat quadraticVal)
{
	glLightf(lightNum, GL_CONSTANT_ATTENUATION, constantVal);
	glLightf(lightNum, GL_LINEAR_ATTENUATION, linearVal);
	glLightf(lightNum, GL_QUADRATIC_ATTENUATION, quadraticVal);
}