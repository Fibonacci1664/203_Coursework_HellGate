#include "Ground.h"


Ground::Ground()
{
	initGround();
}

Ground::~Ground()
{

}

void Ground::render()
{
	renderCobblePlane();
}

void Ground::initGround()
{
	cobbleGround = new Model();
	cobbleGround->load(cobbleGroundFilePath, cobbleGroundTexPath);
}

void Ground::renderCobblePlane()
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			cobbleGround->render();

			if (col == 3)
			{
				continue;
			}

			if (row % 2 == 0)
			{
				glTranslatef(7.65f, 0, 0);
			}
			else
			{
				glTranslatef(-7.65f, 0, 0);
			}
		}

		// Once we have rendered a row we must "drop down" (z-axis) and render another row.
		glTranslatef(0, 0, 7.65f);
	}
}