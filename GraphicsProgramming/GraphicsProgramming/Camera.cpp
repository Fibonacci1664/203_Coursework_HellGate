/*
* 
* A class which controls the movement of a camera by either key press or
* by both mouse and key press.
* 
* Original @author D. Green.
*
* © D. Green. 2020.
* 
 */

 ///////////////////////////////////////////////////////////////////////////////////////////

#include "Camera.h"

///////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR / DESTRUCTOR
Camera::Camera(Input* in) : input(in)
{
	moveSpeed = 10.0f;
	rotationSpeed = 20.0f;
	rotating = false;
	firstUpdate = true;
	mouseX = 0;
	mouseY = 0;
	mouseXDiff = 0;
	mouseYDiff = 0;

	// Initialize the camera with some starting values.
	initCamStartingPos();
	initRotationVals();
	initForwardVec();
	initRightVec();
}

Camera::~Camera()
{

}
// END CONSTRUCTOR / DESTRUCTOR

///////////////////////////////////////////////////////////////////////////////////////////

// CLASS FUNCTIONS
void Camera::handleInput(float dt)
{
	if (firstRender)
	{
		windowCentreX = *windowWidth / 2;
		windowCentreY = *windowHeight / 2;
		input->setMouseX(windowCentreX);
		input->setMouseY(windowCentreY);
		mouseX = windowCentreX;
		mouseY = windowCentreY;
		firstRender = false;
	}

	checkKeyboardInput(dt);
	checkMouseInput(dt);	
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::update(float dt)
{
	// TEMPS WERE HERE, BUT AS WE NEED TO ONLY CALC THE ROTATIONS AS AND WHEN ROTATIONS HAPPEN
	// WE MUST HAVE THOSE VARIABLES CALCULATED IN A CONDITIONAL CODE BLOCK WHICH MEANT THE COMPILER
	// WAS COMPLAINING THAT THERE WAS POTENTIAL TO USE UNINITIALISED VARIABLES FOR THE FORWARD VECTOR
	// IF BOTH CONDITIONS EVALUATED TO FALSE WHEN THE PROGRAM IS FIRST RUN. AS FIRSTUPDATE IS SET TO
	// TRUE IN THE CONSTRUCTOR THIS IS UNLIKELY. HOWEVER TO PREVENT THIS FROM POTENTIALLY HAPPNENING
	// SHOULD THE CONTRUCTOR VALUE BE CHANGED I MOVED THE "TEMP" VARIABLES TO THE .H FILE MAKING THEM
	// DATA MEMBERS, SHOULD I HAVE DONE THIS? WHAT IS THE RATIONALE FOR HAVING THEM AS TEMPS IN THE
	// UPDATE FUNCTION AND NOT DATA MEMBERS??

	if (firstUpdate || rotating)
	{
		firstUpdate = false;
		rotating = false;

		// Roll, Pitch and Yaw are variables stored by the camera
		// handle rotation
		// Only want to calculate these values once, when rotation changes, not every frame.
		cosY = cosf(yaw * 3.1415 / 180);		// In initial val = 1
		cosP = cosf(pitch * 3.1415 / 180);		// In initial val = 1
		cosR = cosf(roll * 3.1415 / 180);		// In initial val = 1
		sinY = sinf(yaw * 3.1415 / 180);		// In initial val = 0
		sinP = sinf(pitch * 3.1415 / 180);		// In initial val = 0
		sinR = sinf(roll * 3.1415 / 180);		// In initial val = 0
	}

	// This using the parametric equation of a sphere
	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector
	forward.x = sinY * cosP;			// In initial val = 0
	forward.y = sinP;					// In initial val = 0
	forward.z = cosP * -cosY;			// In initial val = -1

	// Look At Point
	// To calculate add Forward Vector to Camera position.
	lookAt = position + forward;

	// The equivalent but in long form.
	/*lookAt.x = position.x + forward.x;
	lookAt.y = position.y + forward.y;
	lookAt.z = position.z + forward.z;*/

	// Up Vector
	up.x = (-cosY * sinR) - (sinY * sinP * cosR);		// In initial val = 0
	up.y = cosP * cosR;									// In initial val = 1
	up.z = (-sinY * sinR) - (sinP * cosR * -cosY);		// In initial val = 0
	
	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this, don’t do it.
	right = forward.cross(up);

	// Update mouse position.
	mouseX = input->getMouseX();
	mouseY = input->getMouseY();

	// Calculate difference between mouse pos and window centre in both x and y.
	mouseXDiff = mouseX - windowCentreX;
	mouseYDiff = mouseY - windowCentreY;
	glutWarpPointer(windowCentreX, windowCentreY);
}
// END UPDATE FUNCTION.

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::checkKeyboardInput(float dt)
{
	if (input->isKeyDown('w'))
	{
		// Move forward
		moveForward(dt);
	}

	if (input->isKeyDown('a'))
	{
		// Strafe left
		strafeLeft(dt);
	}

	if (input->isKeyDown('s'))
	{
		// Move back
		moveBackward(dt);
	}

	if (input->isKeyDown('d'))
	{
		// Strafe right
		strafeRight(dt);
	}

	if (input->isKeyDown('r'))
	{
		// Move up
		moveUp(dt);
	}

	if (input->isKeyDown('f'))
	{
		// Move down
		moveDown(dt);
	}

	//if (input->isKeyDown('i'))
	//{
	//	// Look up.
	//	lookUp(dt);
	//	rotating = true;
	//}

	//if (input->isKeyDown('k'))
	//{
	//	// Look down.
	//	lookDown(dt);
	//	rotating = true;
	//}

	//if (input->isKeyDown('j'))
	//{
	//	// Look left.
	//	lookLeft(dt);
	//	rotating = true;
	//}

	//if (input->isKeyDown('l'))
	//{
	//	// Look right.
	//	lookRight(dt);
	//	rotating = true;
	//}

	//if (input->isKeyDown('n'))
	//{
	//	// Tilt left.
	//	rollLeft(dt);
	//	rotating = true;
	//}

	//if (input->isKeyDown('m'))
	//{
	//	// Tilt right.
	//	rollRight(dt);
	//	rotating = true;
	//}
}
// END CHECK KEYBOARD INPUT FUNCTION.

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::checkMouseInput(float dt)
{
	if (mouseX < windowCentreX)
	{
		// MouseDiff will be neg.
		float move = -mouseXDiff * dt;

		lookLeft(move);
		rotating = true;
	}

	if (mouseX > windowCentreX)
	{
		// MouseDiff will be pos.
		float move = mouseXDiff * dt;

		lookRight(move);
		rotating = true;
	}

	if (mouseY < windowCentreY)
	{
		float move = -mouseYDiff * dt;

		lookUp(move);
		rotating = true;
	}

	if (mouseY > windowCentreY)
	{
		float move = mouseYDiff * dt;

		lookDown(move);
		rotating = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::initCamStartingPos()
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 6.0f;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = -1.0f;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::initRotationVals()
{
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::initForwardVec()
{
	forward.x = 0.0f;
	forward.y = 0.0f;
	forward.z = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::initRightVec()
{
	right.x = 0.0f;
	right.y = 0.0f;
	right.z = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::moveForward(float dt)
{
	position.add(forward, moveSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::moveBackward(float dt)
{
	position.subtract(forward, moveSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::moveUp(float dt)
{
	// Move up using the up vector.
	//position.add(up, moveSpeed * dt);

	// Move up by simply increasing the y-axis value.
	position.y += (moveSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::moveDown(float dt)
{
	// Move down using the up vector.
	//position.subtract(up, moveSpeed * dt);

	// Move down by simply decreasing the y-axis value.
	position.y -= (moveSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::strafeRight(float dt)
{
	position.add(right, moveSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::strafeLeft(float dt)
{
	position.subtract(right, moveSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::lookLeft(float dt)
{
	yaw -= (rotationSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::lookRight(float dt)
{
	yaw += (rotationSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::lookUp(float dt)
{
	pitch += (rotationSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::lookDown(float dt)
{
	pitch -= (rotationSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::rollLeft(float dt)
{
	roll -= (rotationSpeed * dt);
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::rollRight(float dt)
{
	roll += (rotationSpeed * dt);
}

// END CLASS FUNCTIONS.

///////////////////////////////////////////////////////////////////////////////////////////

// GETTERS AND SETTERS.
Vector3 Camera::getPos()
{
	return position;
}

///////////////////////////////////////////////////////////////////////////////////////////

Vector3 Camera::getLookAt()
{
	return lookAt;
}

///////////////////////////////////////////////////////////////////////////////////////////

Vector3 Camera::getUp()
{
	return up;
}

///////////////////////////////////////////////////////////////////////////////////////////

Vector3 Camera::getForward()
{
	return forward;
}

///////////////////////////////////////////////////////////////////////////////////////////

float Camera::getMoveSpeed()
{
	return moveSpeed;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::setMoveSpeed(float newSpeed)
{
	moveSpeed = newSpeed;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::setWindowWidth(int* winWidth)
{
	windowWidth = winWidth;
}

///////////////////////////////////////////////////////////////////////////////////////////

void Camera::setWindowHeight(int* winHeight)
{
	windowHeight = winHeight;
}
// END GETTERS AND SETTERS.

// END CLASS.
