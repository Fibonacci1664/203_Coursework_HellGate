#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	

	// Initialise scene variables
	m_wireFrame = false;
	m_planetRotation = 0;
	m_planetRotationSpeed = 5.0f;
	initCamera();
	initSkySphere();
	initGround();
	initPlanetarySystem();
}

Scene::~Scene()
{
	delete cam;
	delete skySphere;
	delete ground;
}

void Scene::handleInput(float dt)
{
	// Handle user input
	cam->handleInput(dt);
	toggleWireFrame();
}

void Scene::update(float dt)
{
	m_planetRotation += (m_planetRotationSpeed * dt);

	// update scene related variables.
	cam->update(dt);
	skySphere->update(dt);

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render()
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	//gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(cam->getPos().x, cam->getPos().y, cam->getPos().z,
		cam->getLookAt().x, cam->getLookAt().y, cam->getLookAt().z,
		cam->getUp().x, cam->getUp().y, cam->getUp().z);
	
	// Render geometry/scene here -------------------------------------

	// Render a unit skysphere around the camera.
	glPushMatrix();
		glTranslatef(cam->getPos().x, cam->getPos().y, cam->getPos().z);
		skySphere->render();
	glPopMatrix();

	// Render a plane of cobble stone ground.
	glPushMatrix();
		ground->render();
	glPopMatrix();

	// Render a planetary system
	renderPlanetarySystem();

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearColor(0, 0, 0, 1.0f);						// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

//////////////////////////////////////////////////////////// CAMERA STUFF ////////////////////////////////////////////////////////////

void Scene::initCamera()
{
	cam = new Camera(input);
	cam->setWindowWidth(&width);
	cam->setWindowHeight(&height);
}

//////////////////////////////////////////////////////////// SKYSPHERE STUFF //////////////////////////////////////////////////////////

void Scene::initSkySphere()
{
	skySphere = new SkySphere(1, 50, 50);
}

//////////////////////////////////////////////////////////// SPHERE STUFF /////////////////////////////////////////////////////////////

void Scene::initPlanetarySystem()
{
	planet = new Sphere(12, 30, 30, m_alienWorldTexPath);
	moon = new Sphere(3, 10, 10, m_moonTexPath);
	moonOfMoon = new Sphere(1, 10, 10, m_moonOfMoonTexPath);
}

void Scene::renderPlanetarySystem()
{
	glPushMatrix();
		glTranslatef(0, 100.0f, -200.0f);
		glRotatef(-23.5f, 0, 0, 1.0f);
		glRotatef(m_planetRotation, 0, 1.0f, 0);
		planet->render();

		glPushMatrix();
			glTranslatef(48.0f, 0, 0);
			glRotatef(m_planetRotation * 2, 0, 1.0f, 0);
			moon->render();

			glPushMatrix();
				glTranslatef(12.0f, 0, 0);
				glRotatef(m_planetRotation * 3, 0, 0, 1.0f);
				moonOfMoon->render();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// TEXTURE STUFF ////////////////////////////////////////////////////////////

void Scene::enableTextures()
{
	glEnable(GL_TEXTURE_2D);
}

void Scene::disableTextures()
{
	glDisable(GL_TEXTURE_2D);
}

//////////////////////////////////////////////////////////// LOADED MODEL STUFF ///////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// GROUND MODEL STUFF ///////////////////////////////////////////////////////

void Scene::initGround()
{
	ground = new Ground();
}

//////////////////////////////////////////////////////////// GENERAL SCENE STUFF //////////////////////////////////////////////////////

void Scene::toggleWireFrame()
{
	if (input->isKeyDown('p') && !m_wireFrame)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		m_wireFrame = true;
		input->setKeyUp('p');
		planet->setWireFrameMode(true);
		moon->setWireFrameMode(true);
		moonOfMoon->setWireFrameMode(true);
	}

	if (input->isKeyDown('p') && m_wireFrame)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		m_wireFrame = false;
		input->setKeyUp('p');
		planet->setWireFrameMode(false);
		moon->setWireFrameMode(false);
		moonOfMoon->setWireFrameMode(false);
	}
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 500.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);

	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}

	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
