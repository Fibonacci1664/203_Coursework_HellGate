#include "Material.h"

Material::Material()
{
	
}

Material::~Material()
{

}

// For real world objects, amb and diff reflection are generally the same colour, I have 2 seperate vars in my Scene.h but passing
// in just one of the amb or diff values will set both to that colour as I have specified, GL_AMBIENT_AND_DIFFUSE.
void Material::createMaterial(GLfloat mat_amb_col[], GLfloat mat_diff_col[], GLfloat mat_spec_col[], GLfloat shininess)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_col);
	glMaterialfv(GL_FRONT, GL_EMISSION, _no_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec_col);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}

void Material::createEmisssionMat(GLfloat mat_amb_col[], GLfloat mat_diff_col[], GLfloat mat_spec_col[], GLfloat emission[], GLfloat shininess)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_col);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec_col);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
}
