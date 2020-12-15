#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class Material
{
public:
	Material();
	~Material();

	void createMaterial(GLfloat mat_amb_col[], GLfloat mat_diff_col[], GLfloat mat_spec_col[], GLfloat shininess);
	void createEmisssionMat(GLfloat mat_amb_col[], GLfloat mat_diff_col[], GLfloat mat_spec_col[], GLfloat emission[], GLfloat shininess);


protected:

private:
	GLfloat _no_mat[4] = { 0, 0, 0, 0 };
	GLfloat _no_shine[4] = { 0, 0, 0, 0 };
};

