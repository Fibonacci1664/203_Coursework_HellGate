/*
 * About this class
 *		- The main scene, initilises everything in the scene including req. OpenGL settings.
 *		- Interfaces with the Input class to handle user input.
 *		- Handles some input directly for scene class related features.
 *		- Loads in shadow textures as there is no stand alone shadow class.
 *		- Updates cam and skysphere obejcts.
 *		- Calculates FPS.
 *		- Renders all objects in scene in specific order.
 *
 * Original @author D. Green.
 *
 * © D. Green. 2020.
 */

///////////////////////////////////////////////////////////////////////////////////////////

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
#include "DragonPortal.h"
#include "Brazier.h"
#include "RockyLand.h"
#include "Altar.h"
#include "Skull.h"
#include "Candle.h"
#include "Page.h"
#include "Material.h"
#include "SpellEffect.h"

///////////////////////////////////////////////////////////////////////////////////////////

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
	void initTextures();
	void renderCameraPosText();

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

	////////////////////////////////// CAMERA STUFF /////////////////////////////////
	// CAMERA FUNCS
	void initCamera();

	// CAMERA VARS
	Camera* cam;
	bool camera_1;
	bool camera_2;
	bool motionCam;
	float cameraZoom;
	float cameraZoomSpeed;
	char cameraPosXText[40];
	char cameraPosYText[40];
	char cameraPosZText[40];
	char cameraLookXText[40];
	char cameraLookYText[40];
	char cameraLookZText[40];

	////////////////////////////////// CREATED GEOMETRY STUFF ////////////////////////

	////////////////////////////////// SKYSPHERE STUFF ///////////////////////////////
	// SKYSPHERE FUNCS
	void initSkySphere();
	void renderSkySphere();
	void renderSkySphere2();
	
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

	////////////////////////////////// CAGE STUFF /////////////////////////////////////
	// CAGE FUNCS
	void initCage();
	void renderCages();

	// CAGE VARS
	Cage* cage;

	////////////////////////////////// CRATE STUFF ////////////////////////////////////
	// CRATE FUNCS
	void initCrate();
	void renderCrates();

	// CRATE VARS
	Crate* crate;

	////////////////////////////////// PLANK STUFF ////////////////////////////////////
	// PLANK FUNCS
	void initPlank();
	void renderPlanks();

	// PLANK VARS
	Plank* plank;

	////////////////////////////////// DISC STUFF /////////////////////////////////////
	// COIN FUNCS
	void initCoin();
	void renderCoin();

	// COIN VARS
	Disc* coin;
	char* m_coinTexPath = "gfx/textures/goldCoin.png";

	// CANDLE FUNCS
	void initCandle();
	void renderCandles();

	// CANDLE VARS
	Candle* candle;
	char* m_candleTexPath = "gfx/textures/candleWax.jpg";
	Material emission_mat;		// For the flame of the center candle.

	// EMISSION MATERIAL FOR FLAME LOCATION
	GLfloat mat_amb_col[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat mat_diff_col[4] = { 0.878f, 0.616f, 0.216f, 1.0f };		// ALWAYS KEEP SPECULAR AND DIFFUSE SIMILAR IF NOT IDENTICAL.
	GLfloat mat_spec_col[4] = { 0.878f, 0.616f, 0.216f, 1.0f };
	GLfloat mat_emission_col[4] = { 0, 0, 0, 1.0f };

	// SPELL FUNCS
	void initSpellEffect();
	void renderSpellEffect();

	// SPELL VARS
	SpellEffect* spell;
	float spellRotation;
	float spellRotationSpeed;
	bool pageClicked;
	float spellEffectAlpha;

	////////////////////////////////// ALTAR STUFF ////////////////////////////////////
	// ALTAR FUNCS
	void initAltar();
	void renderAltar();

	// ALTAR VARS
	Altar* altar;

	////////////////////////////////// PAGES STUFF ////////////////////////////////////
	// PAGES FUNCS
	void initPage();
	void renderPages();

	// PAGES VARS
	Page* page_1;
	Page* page_2;
	Page* page_3;

	char* evilPage_1Path = "gfx/textures/evilPage_1.png";
	char* evilPage_2Path = "gfx/textures/evilPage_2.jpg";
	char* evilPage_3Path = "gfx/textures/evilPage_3.jpg";

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

	////////////////////////////////// SKULL MODEL STUFF ///////////////////////////////
	// SKULL FUNCS
	void initSkull();
	void renderSkulls();

	// SKULL VARS
	Skull* skull;

	////////////////////////////////// ROCKY LAND MODEL STUFF //////////////////////////
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


	// STENCIL VARS

	////////////////////////////////// SHADOW STUFF ///////////////////////////////////
	// SHADOW FUNCS
	void imposter();
	void drawTexQuad(float scale, GLuint texture);

	// SHADOW VARS
	GLuint imposterTex;
	char* imposterTexPath = "gfx/textures/imposter.png";
	Light candleLight;

	// Light properties
	GLfloat candleLightAmbience[4] = { 0.3f, 0.1f, 0.03f, 1.0f };
	GLfloat candleLightDiffuse[4] = { 0.878f, 0.616f, 0.216f, 1.0f };
	// Point
	GLfloat candleLightPosition[4] = { 0, 0, 0, 1 };			// w = 0 = direction, w = 1 = point light

	float lightX = 0, lightY = 0, lightZ = 0;
	float lightSpeed = 20;
};

#endif

///////////////////////////////////////////////////////////////////////////////////////////