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
#include "Light.h"
#include "Cage.h"
#include "Crate.h"
#include "Plank.h"
#include "Coin.h"
#include "DragonPortal.h"
#include "Brazier.h"
#include "RockyLand.h"


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

	bool m_wireFrame;
	
	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	////////////////////////////////// LIGHTING STUFF ///////////////////////////////
	// LIGHT FUNCS

	// LIGHT VARS
	Light brownDwarfPointLight_1;
	Light brownDwarfPointLight_2;
	Light brownDwarfPointLight_3;
	Light brownDwarfPointLight_4;
	Light coalGlow_1;
	Light coalGlow_2;

	// Light properties
	GLfloat brownDwarfLightAmbient[4] = { 0.3f, 0.1f, 0.03f, 1.0f };
	GLfloat brownDwarfLightDiffuse[4] = { 0.3f, 0.1f, 0.03f, 1.0f };
	GLfloat coalGlowLightAmbient[4] = { 0.48f, 0.24f, 0.17f, 1.0f };
	GLfloat coalGlowLightDiffuse[4] = { 0.97f, 0.48f, 0.34f, 1.0f };
	// Spot
	GLfloat coalGlowSpotDirection[3] = { 0.0f, -1.0f, 0.0f };
	// Point
	GLfloat brownDwarfLightPosition_1[4] = { 40.0f, 0, 0, 1 };			// w = 0 = direction, w = 1 = point light
	GLfloat brownDwarfLightPosition_2[4] = { -40.0f, 0, 0, 1 };			// w = 0 = direction, w = 1 = point light
	GLfloat brownDwarfLightPosition_3[4] = { 0, 40.f, 0, 1 };			// w = 0 = direction, w = 1 = point light
	GLfloat brownDwarfLightPosition_4[4] = { 0, -40.f, 0, 1 };			// w = 0 = direction, w = 1 = point light
	GLfloat coalGlowLightPosition[4] = { 0, 6.0f, 0, 1 };			// w = 0 = direction, w = 1 = point light

	////////////////////////////////// CAMERA STUFF //////////////////////////////////
	// CAMERA FUNCS
	void initCamera();

	// CAMERA VARS
	Camera* cam;

	////////////////////////////////// SKYSPHERE STUFF ///////////////////////////////
	// SKYSPHERE FUNCS
	void initSkySphere();
	void renderSkySphere();
	
	// SKYSPHERE VARS
	SkySphere* skySphere;

	////////////////////////////////// SPHERE STUFF //////////////////////////////////
	// PLANET STUFF
	// PLANET FUNCS
	void initPlanetarySystem();
	void renderPlanetarySystem();

	// PLANET VARS
	Sphere* brownDwarf;
	Sphere* planet;
	Sphere* planetAtmos;
	Sphere* moon;
	Sphere* moonOfMoon;
	char* m_moonTexPath = "gfx/textures/grey_moon_fic.jpg";
	char* m_moonOfMoonTexPath = "gfx/textures/redMoon.jpg";
	char* m_alienWorldTexPath = "gfx/textures/alien_world.png";
	char* m_brownDwarfTexPath = "gfx/textures/darkSun_2.png";
	char* m_atmosTexPath = "gfx/textures/atmosphere.png";
	float m_planetRotation;
	float m_planetRotationSpeed;

	// COAL FUNCS
	void initCoal();
	void renderCoal();

	// COAL VARS
	Sphere* lumpOfCoal;
	char* m_hotCoalTexPath = "gfx/textures/hotCoal.jpg";

	////////////////////////////////// CAGE STUFF ////////////////////////////////////
	// CAGE FUNCS
	void initCage();
	void renderCages();

	// CAGE VARS
	Cage* cage;

	////////////////////////////////// CRATE STUFF ///////////////////////////////////
	// CRATE FUNCS
	void initCrate();
	void renderCrates();

	// CRATE VARS
	Crate* crate;

	////////////////////////////////// PLANK STUFF ///////////////////////////////////
	// PLANK FUNCS
	void initPlank();
	void renderPlanks();

	// PLANK VARS
	Plank* plank;

	////////////////////////////////// COIN STUFF ////////////////////////////////////
	// COIN FUNCS
	void initCoin();
	void renderCoin();

	// COIN VARS
	Coin* coin;
	
	////////////////////////////////// TEXTURE STUFF (PROB WONT NEED THIS!) ///////////
	// TEXTURE FUNCS
	void enableTextures();
	void disableTextures();

	////////////////////////////////// LOADED MODEL STUFF /////////////////////////////

	////////////////////////////////// GROUND MODEL STUFF /////////////////////////////
	// GROUND MODEL FUNCS
	void initGround();
	void renderGround();
	
	// GROUND MODEL VARS
	Ground* ground;

	////////////////////////////////// DRAGON PORTAL MODEL STUFF //////////////////////
	// DRAGON PORTAL FUNCS
	void initDragonPortal();
	void renderDragonPortal();

	// DRAGON PORTAL VARS
	DragonPortal* portal;

	////////////////////////////////// BRAZIER MODEL STUFF ////////////////////////////
	// BRAZIER FUNCS
	void initBrazier();
	void renderBraziers();

	// BRAZIER VARS
	Brazier* brazier;

	////////////////////////////////// ROCKY LAND MODEL STUFF ////////////////////////////
	// ROCKY LAND FUNC
	void initRockyLand();
	void renderRockyLand();

	// ROCKY LAND VARS
	RockyLand* rockyLand;

	////////////////////////////////// STENCIL BUFFER STUFF ////////////////////////////
	// STENCIL FUNCS
	void buildStencilPortalShape();
	void buildStencil();
	void buildMirrorUniverse();
	void buildRealUniverse();


	// STENCIL VARS;

};

#endif