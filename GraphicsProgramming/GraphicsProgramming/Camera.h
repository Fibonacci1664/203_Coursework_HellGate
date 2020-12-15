/*
* About this class
*		- Controls the movement of a camera by either key press or
*			by both mouse and key press.
*
* Original @author D. Green.
*
* © D. Green. 2020.
*
 */

///////////////////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////

#include "Vector3.h"
#include "Input.h"
#include <glut.h>

///////////////////////////////////////////////////////////////////////////////////////////

class Camera
{
public:
	Camera(Input* input);
	~Camera();

	void handleInput(float dt);
	void update(float dt);

	void checkKeyboardInput(float dt);
	void checkMouseInput(float dt);

	void moveForward(float dt);
	void moveBackward(float dt);
	void moveUp(float dt);
	void moveDown(float dt);
	void strafeRight(float dt);
	void strafeLeft(float dt);
	void lookLeft(float dt);
	void lookRight(float dt);
	void lookUp(float dt);
	void lookDown(float dt);
	void rollLeft(float dt);
	void rollRight(float dt);

	Vector3 getPos();
	Vector3 getLookAt();
	Vector3 getUp();
	Vector3 getForward();
	float getMoveSpeed();

	void setMoveSpeed(float newSpeed);
	void setWindowWidth(int* widWidth);
	void setWindowHeight(int* winHeight);
	
protected:
	Input* input;

private:
	void initCamStartingPos();
	void initRotationVals();
	void initForwardVec();
	void initRightVec();

	Vector3 position;
	Vector3 lookAt;
	Vector3 up;
	Vector3 forward;
	Vector3 right;
	float yaw;
	float pitch;
	float roll;

	float moveSpeed;
	float rotationSpeed;

	// Bools to control access the the rotational calcs done in update.
	bool rotating;
	bool firstUpdate;

	// WHY WERE THESE AS TEMPS IN THE UDPATE??
	float cosR, cosP, cosY;			// temp values for sin/cos from
	float sinR, sinP, sinY;
	
	float mouseX;
	float mouseY;
	float mouseXDiff;
	float mouseYDiff;
	int* windowWidth;
	int* windowHeight;
	int windowCentreX;
	int windowCentreY;

	bool firstRender = true;
};

///////////////////////////////////////////////////////////////////////////////////////////