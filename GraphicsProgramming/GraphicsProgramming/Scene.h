// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "SkySphere.h"
#include "Model.h"
#include "Ground.h"
#include "Sphere.h"


class Scene
{

public:
	Scene(Input *in);
	~Scene();
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();
	void toggleWireFrame();

	bool wireFrame;
	
	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	////////////////////////////////// CAMERA STUFF //////////////////////////////////
	// CAMERA FUNCS
	void initCamera();

	// CAMERA VARS
	Camera* cam;

	////////////////////////////////// SKYSPHERE STUFF ///////////////////////////////
	// SKYSPHERE FUNCS
	void initSkySphere();
	
	// SKYSPHERE VARS
	SkySphere* skySphere;

	////////////////////////////////// SPHERE STUFF ///////////////////////////////
	// SPHERE FUNCS
	void initPlanetarySystem();

	// SPHERE VARS
	Sphere* planet;
	
	////////////////////////////////// TEXTURE STUFF //////////////////////////////////
	// TEXTURE FUNCS
	void enableTextures();
	void disableTextures();

	////////////////////////////////// LOADED MODEL STUFF /////////////////////////////

	////////////////////////////////// GROUND MODEL STUFF /////////////////////////////

	// GROUND MODEL VARS
	Ground* ground;

	// GROUND MODEL FUNCS
	void initGround();
};

#endif