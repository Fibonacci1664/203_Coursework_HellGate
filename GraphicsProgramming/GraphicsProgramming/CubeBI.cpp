#include "CubeBI.h"

CubeBI::CubeBI()
{

}

CubeBI::~CubeBI()
{

}

void CubeBI::render(GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	enableArrays();
	arrayDataArrangment();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubeBuildIndex);
	disableArrays();
	glDisable(GL_TEXTURE_2D);
}

void CubeBI::enableArrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void CubeBI::disableArrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void CubeBI::arrayDataArrangment()
{
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
}