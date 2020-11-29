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
	// Move plane 3 units below the camera eye.
	glTranslatef(0.0f, -3.0f, 0.0f);

	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 5; ++col)
		{
			cobbleGround->render();

			if (col == 4)
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