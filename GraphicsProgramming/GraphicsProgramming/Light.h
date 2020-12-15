/*
 * About this class
 *		- Contains functions to render lights of type:
 *			- Directional.
 *			- Point.
 *			- Spot.
 *			- Specular.
 *		- (NOTE!) Lights are enabled from within the functions when rendered.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>

///////////////////////////////////////////////////////////////////////////////////////////

class Light
{
public:
	Light();
	~Light();

	void renderDirectionalLight(GLenum lightNum, GLfloat diffuse[], GLfloat position[]);
	void renderPointLight(GLenum lightNum, GLfloat ambience[], GLfloat diffuse[], GLfloat position[]);
	void renderSpotLight(GLenum lightNum, GLfloat ambience[], GLfloat diffuse[], GLfloat position[], GLfloat spot_dir[]);
	void renderSpecularLight(GLenum lightNum, GLfloat ambience[], GLfloat diffuse[], GLfloat position[], GLfloat specular[]);
	void setAttenuation(GLenum lightNum, GLfloat constantVal, GLfloat linearVal, GLfloat quadraticVal);

protected:

private:

};

///////////////////////////////////////////////////////////////////////////////////////////