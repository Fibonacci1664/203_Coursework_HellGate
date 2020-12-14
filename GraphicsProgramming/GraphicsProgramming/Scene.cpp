#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_LIGHTING);

	// Initialise scene variables
	m_wireFrame = false;
	m_planetRotation = 0;
	m_planetRotationSpeed = 5.0f;
	initCamera();
	initSkySphere();
	initGround();
	initPlanetarySystem();	
	initCrate();
	initPlank();
	initCoin();
	initDragonPortal();
	initBrazier();
	initCoal();
	initRockyLand();
	initAltar();
	initSkull();
	initCandle();
	initPage();




	// THIS IS LAST.
	initCage();
}

Scene::~Scene()
{
	delete cam;
	cam = nullptr;

	delete skySphere;
	skySphere = nullptr;

	delete ground;
	ground = nullptr;

	delete brownDwarf;
	brownDwarf = nullptr;

	delete planet;
	planet = nullptr;

	delete planetAtmos;
	planetAtmos = nullptr;

	delete moon;
	moon = nullptr;

	delete moonOfMoon;
	moonOfMoon = nullptr;

	delete cage;
	cage = nullptr;

	delete crate;
	crate = nullptr;

	delete plank;
	plank = nullptr;

	delete coin;
	coin = nullptr;

	delete portal;
	portal = nullptr;

	delete brazier;
	brazier = nullptr;

	delete lumpOfCoal;
	lumpOfCoal = nullptr;

	delete rockyLand;
	rockyLand = nullptr;

	delete altar;
	altar = nullptr;

	delete skull;
	skull = nullptr;

	delete candle;
	candle = nullptr;

	delete page_1;
	page_1 = nullptr;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	//gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(cam->getPos().x, cam->getPos().y, cam->getPos().z,
		cam->getLookAt().x, cam->getLookAt().y, cam->getLookAt().z,
		cam->getUp().x, cam->getUp().y, cam->getUp().z);
	
	// Render geometry/scene here -------------------------------------
	// Build stencil for dragon portal.
	//buildStencil();
	
	// Build mirror world inside the dragon protal.
	//buildMirrorUniverse();

	// Build real world.
	//buildRealUniverse();

	// Render a unit skysphere around the camera.
	renderSkySphere();

	// Render a plane of cobble stone ground.
	renderGround();

	// Render a planetary system
	renderPlanetarySystem();

	// Render crates.
	renderCrates();

	// Render planks.
	renderPlanks();

	// Render a cart wheel
	renderCoin();

	// Render a dragon portal
	renderDragonPortal();

	// Render braziers either side of the dragon portal.
	renderBraziers();

	// Render lumps of coal glowing in the braziers.
	renderCoal();

	// Render the altar
	renderAltar();

	// Render skulls sitting on the altar.
	renderSkulls();

	// Render candles on the altar.
	renderCandles();

	// Render evil ritual pages on the altar.
	renderPages();


	


	// Render cages. THESE NEED TO BE LAST THING RENDERED!
	renderCages();

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
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	//glClearColor(0, 0, 0, 1.0f);						// Black Background
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

//////////////////////////////////////////////////////////// CAMERA STUFF END /////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// SKYSPHERE STUFF //////////////////////////////////////////////////////////

void Scene::initSkySphere()
{
	skySphere = new SkySphere(1, 50, 50);
}

void Scene::renderSkySphere()
{
	glPushMatrix();
		glTranslatef(cam->getPos().x, cam->getPos().y, cam->getPos().z);
		skySphere->render();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// SKYSPHERE STUFF END //////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// ALL SPHERE STUFF /////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// PLANET STUFF /////////////////////////////////////////////////////////////

void Scene::initPlanetarySystem()
{
	brownDwarf = new Sphere(36, 40, 40, m_brownDwarfTexPath);
	planet = new Sphere(12, 30, 30, m_alienWorldTexPath);
	planetAtmos = new Sphere(12.3f, 30, 30, m_atmosTexPath);
	moon = new Sphere(3, 10, 10, m_moonTexPath);
	moonOfMoon = new Sphere(1, 10, 10, m_moonOfMoonTexPath);
}

void Scene::renderPlanetarySystem()
{
	glPushMatrix();													// Save world origin.
		glTranslatef(0, -100.0f, -200.0f);
		glRotatef(m_planetRotation / 2.0f, 0, 1.0f, 0);		
		brownDwarf->render();
		/*brownDwarfPointLight_1.renderPointLight(GL_LIGHT0, brownDwarfLightAmbient, brownDwarfLightDiffuse, brownDwarfLightPosition_1);
		brownDwarfPointLight_2.renderPointLight(GL_LIGHT1, brownDwarfLightAmbient, brownDwarfLightDiffuse, brownDwarfLightPosition_2);
		brownDwarfPointLight_3.renderPointLight(GL_LIGHT2, brownDwarfLightAmbient, brownDwarfLightDiffuse, brownDwarfLightPosition_3);
		brownDwarfPointLight_4.renderPointLight(GL_LIGHT3, brownDwarfLightAmbient, brownDwarfLightDiffuse, brownDwarfLightPosition_4);*/
		
		/*glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);*/

		glPushMatrix();												// Save brown dwarf origin.
			
			glTranslatef(150.f, 0, 0);
			glRotatef(m_planetRotation, 0, 1.0f, 0);
			planet->render();
			glRotatef(m_planetRotation / 1.5f, 0, 1.0f, 0);
			glEnable(GL_BLEND);
			planetAtmos->render();
			glDisable(GL_BLEND);


			glPushMatrix();											// Save alien planet origin.
				glTranslatef(48.0f, 0, 0);
				glRotatef(m_planetRotation * 2, 0, 1.0f, 0);
				moon->render();

				glPushMatrix();										// Save moon origin.
					glTranslatef(12.0f, 0, 0);
					glRotatef(m_planetRotation * 3, 0, 0, 1.0f);
					moonOfMoon->render();
				glPopMatrix();										// Back to moon.
			glPopMatrix();											// Back to planet.
		glPopMatrix();												// Back to brown dwarf.
	glPopMatrix();													// Back to world origin.
}

//////////////////////////////////////////////////////////// PLANET STUFF END ////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// LUMP COAL STUFF /////////////////////////////////////////////////////////////

void Scene::initCoal()
{
	lumpOfCoal = new Sphere(0.1f, 5, 5, m_hotCoalTexPath);
}

void Scene::renderCoal()
{
	float theta = 5;
	float delta = 9;
	float incTheta = 9;
	float incDelta = 5;

	glPushMatrix();
		glTranslatef(15.0f, 3.9f, 23.0f);
		lumpOfCoal->render();
		coalGlow_1.renderSpotLight(GL_LIGHT4, coalGlowLightAmbient, coalGlowLightDiffuse, coalGlowLightPosition, coalGlowSpotDirection);

		for (int i = 0; i < 20; ++i)
		{
			glPushMatrix();												// Save the original lump of coal location.
				glTranslatef(0.3f * cos(theta), 0, 0.3f * sin(delta));	// Translate a new lump of coal to some locaiton nearby.
				lumpOfCoal->render();
			glPopMatrix();												// Move back to original coal location, and repeat.

			theta += incTheta;
			delta += incDelta;
		}
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5.0f, 3.9f, 23.0f);
		lumpOfCoal->render();
		coalGlow_1.renderSpotLight(GL_LIGHT5, coalGlowLightAmbient, coalGlowLightDiffuse, coalGlowLightPosition, coalGlowSpotDirection);

		for (int i = 0; i < 20; ++i)
		{
			glPushMatrix();												// Save the original lump of coal location.
				glTranslatef(0.3f * cos(theta), 0, 0.3f * sin(delta));	// Translate a new lump of coal to some locaiton nearby.
				lumpOfCoal->render();
			glPopMatrix();												// Move back to original coal location, and repeat.

			theta += incTheta;
			delta += incDelta;
		}
	glPopMatrix();
}

//////////////////////////////////////////////////////////// LUMP COAL STUFF END //////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// ALL SPHERE STUFF END /////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// CAGE STUFF ///////////////////////////////////////////////////////////////

void Scene::initCage()
{
	cage = new Cage();
}

void Scene::renderCages()
{
	glPushMatrix();
		glTranslatef(0, 1.68f, 0);
		cage->render(1.0f);						// Render corner cage.

		glPushMatrix();
			glTranslatef(2.1f, 0, 0);
			cage->render(1.0f);					// Render one to its right.
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, 2.1f);
			cage->render(1.0f);					// Render one to its left.
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 2.0f, 0);
			glRotatef(45.0f, 0, 1.0f, 0);
			cage->render(1.0f);					// Render one on top.
		glPopMatrix();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// CAGE STUFF END ///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// CRATE STUFF //////////////////////////////////////////////////////////////

void Scene::initCrate()
{
	crate = new Crate();
}

void Scene::renderCrates()
{
	glPushMatrix();
		glTranslatef(21.0f, 1.68f, 0);
		crate->render();

		glPushMatrix();
			glTranslatef(-2.1f, 0, 0);
			crate->render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0, 2.1f);
			crate->render();
		glPopMatrix();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// CRATE STUFF END //////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// PLANK STUFF //////////////////////////////////////////////////////////////

void Scene::initPlank()
{
	plank = new Plank();
}

void Scene::renderPlanks()
{
	// Plank 1
	glPushMatrix();
		glTranslatef(18.5f, 2.0f, 2.0f);
		glRotatef(90, 1.0f, 0, 0);
		glRotatef(28, 0, 1.0f, 0);
		glScalef(3.0f, 0.3f, 0.1f);
		plank->render();
	glPopMatrix();

	// Plank 2
	glPushMatrix();
		glTranslatef(17.5f, 1.93f, 1.15f);
		glRotatef(95, 1.0f, 0, 0);
		glRotatef(25, 0, 1.0f, 0);
		glRotatef(25, 0, 0, 1.0f);
		glScalef(3.0f, 0.3f, 0.1f);
		plank->render();
	glPopMatrix();

	// Plank 3
	glPushMatrix();
		glTranslatef(18.7f, 2.0f, 3.1f);
		glRotatef(125, 1.0f, 0, 0);
		glRotatef(30, 0, 1.0f, 0);
		glRotatef(130, 0, 0, 1.0f);		
		glScalef(2.0f, 0.3f, 0.1f);
		plank->render();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// PLANK STUFF END /////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// COIN STUFF //////////////////////////////////////////////////////////////

void Scene::initCoin()
{
	coin = new Disc(30.0f, 0.1f, m_coinTexPath, false, 0.0f);
}

void Scene::renderCoin()
{
	float theta = 5.0f;
	float delta = 9.0f;
	float incTheta = 9.0f;
	float incDelta = 5.0f;

	glPushMatrix();
		glTranslatef(19.0f, 2.7f, 0);
		glRotatef(-90.0f, 1.0f, 0, 0);
		coin->render();

		for (int i = 0; i < 10; ++i)
		{
			glPushMatrix();											// Save the original coins location.
				glTranslatef(0.5f * cos(theta), 0.5f * sin(delta), 0);	// Translate a new coin to some locaiton nearby.
				coin->render();
			glPopMatrix();											// Move back to original coins location, and repeat.

			theta += incTheta;
			delta += incDelta;
		}
	glPopMatrix();
}

//////////////////////////////////////////////////////////// COIN STUFF END ///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// ALTAR STUFF //////////////////////////////////////////////////////////////

void Scene::initAltar()
{
	altar = new Altar();
}

void Scene::renderAltar()
{
	altar->render();
}

//////////////////////////////////////////////////////////// ALTAR STUFF END //////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// CANDLE STUFF /////////////////////////////////////////////////////////////

void Scene::initCandle()
{
	candle = new Candle(20.0f, 0.1f, 1.0f);
}

void Scene::renderCandles()
{
	glPushMatrix();
		glTranslatef(10.0f, 3.9f, 13.0f);
		candle->render();

		glPushMatrix();
			glTranslatef(1.5f, 0, 0);
			glScalef(0.8f, 0.8f, 0.8f);
			candle->render();

			glPushMatrix();
				glTranslatef(1.5f, 0, 0);
				glScalef(0.8f, 0.8f, 0.8f);
				candle->render();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.5f, 0, 0);
			glScalef(0.8f, 0.8f, 0.8f);
			candle->render();

			glPushMatrix();
				glTranslatef(-1.5f, 0, 0);
				glScalef(0.8f, 0.8f, 0.8f);
				candle->render();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// CANDLE STUFF END /////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// PAGES STUFF //////////////////////////////////////////////////////////////

void Scene::initPage()
{
	page_1 = new Page(0.7f, 1.0f, evilPage_1Path);
	page_2 = new Page(0.7f, 1.0f, evilPage_2Path);
	page_3 = new Page(0.7f, 1.0f, evilPage_3Path);
}

void Scene::renderPages()
{
	glPushMatrix();
		glTranslatef(10.35f, 4.0f, 12.4f);
		glRotatef(180.0f, 0, 1.0f, 0);
		page_1->render();

		glPushMatrix();
			glTranslatef(1.5f, 0, 0);
			glRotatef(-20.0f, 0, 1.0f, 0);
			page_2->render();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.5f, 0, 0);
			glRotatef(20.0f, 0, 1.0f, 0);
			page_3->render();
		glPopMatrix();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// PAGES STUFF END //////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// ALL LOADED MODEL STUFF ///////////////////////////////////////////////////

//////////////////////////////////////////////////////////// GROUND MODEL STUFF ///////////////////////////////////////////////////////

void Scene::initGround()
{
	ground = new Ground();
}

void Scene::renderGround()
{
	glPushMatrix();
		ground->render();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// GROUND MODEL STUFF END ///////////////////////////////////////////////////

//////////////////////////////////////////////////////////// DRAGON PORTAL MODEL STUFF ////////////////////////////////////////////////

void Scene::initDragonPortal()
{
	portal = new DragonPortal();
}

void Scene::renderDragonPortal()
{
	glPushMatrix();
		glTranslatef(10.0f, 4.5f, 23.5f);
		glScalef(0.05f, 0.05f, 0.05f);
		portal->render();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// DRAGON PORTAL MODEL STUFF END ////////////////////////////////////////////

//////////////////////////////////////////////////////////// BRAZIER MODEL STUFF //////////////////////////////////////////////////////

void Scene::initBrazier()
{
	brazier = new Brazier();
}

void Scene::renderBraziers()
{
	glPushMatrix();
		glTranslatef(15.0f, 2.50f, 23.0f);
		glScalef(0.015f, 0.015f, 0.015f);
		brazier->render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5.0f, 2.50f, 23.0f);
		glScalef(0.015f, 0.015f, 0.015f);
		brazier->render();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// BRAZIER MODEL STUFF END //////////////////////////////////////////////////

//////////////////////////////////////////////////////////// SKULL MODEL STUFF ////////////////////////////////////////////////////////

void Scene::initSkull()
{
	skull = new Skull();
}

void Scene::renderSkulls()
{
	glPushMatrix();
		glTranslatef(5.8f, 3.95f, 13.0f);
		glRotatef(150.0f, 0, 1.0f, 0);
		glScalef(0.5f, 0.5f, 0.5f);
		skull->render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(14.2f, 3.95f, 13.0f);
		glRotatef(210.0f, 0, 1.0f, 0);
		glScalef(0.5f, 0.5f, 0.5f);
		skull->render();
	glPopMatrix();
}

//////////////////////////////////////////////////////////// SKULL MODEL STUFF END ////////////////////////////////////////////////////

//////////////////////////////////////////////////////////// ROCKY LAND MODEL STUFF END ///////////////////////////////////////////////
void Scene::initRockyLand()
{
	rockyLand = new RockyLand();
}

void Scene::renderRockyLand()
{
	bool blendIsOn = glIsEnabled(GL_BLEND);
	glPushMatrix();
		glTranslatef(10.0f, 5.0f, 55.0f);
		glScalef(0.75f, 0.75f, 0.75f);
		rockyLand->render();
	glPopMatrix();
	blendIsOn = glIsEnabled(GL_BLEND);
}

//////////////////////////////////////////////////////////// STENCIL BUFFER STUFF /////////////////////////////////////////////////////

void Scene::buildStencilPortalShape()
{	
	glTranslatef(9.0f, 2.f, 23.5f);
	glScalef(2.0f, 2.0f, 0);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5f, 0, 0);
		glVertex3f(1.5f, 0, 0);
		glVertex3f(2.2f, 2.2f, 0);
		glVertex3f(1.75f, 3.5f, 0);
		glVertex3f(-0.75f, 3.5f, 0);
		glVertex3f(-1.2f, 2.2f, 0);
	glEnd();
}

void Scene::buildStencil()
{
	// Build Stencil.
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
		// Cutout stencil.	
		buildStencilPortalShape();
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	// End Build Stencil.
}

void Scene::buildMirrorUniverse()
{
	renderRockyLand();
}

void Scene::buildRealUniverse()
{
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	
	// Build a real world portal shape effect.
	glPushMatrix();
		glColor4f(0, 0.47f, 1.0f, 0.3f);
		buildStencilPortalShape();
	glPopMatrix();

	//glDisable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
}

//////////////////////////////////////////////////////////// STENCIL BUFFER STUFF END /////////////////////////////////////////////////

//////////////////////////////////////////////////////////// GENERAL SCENE STUFF //////////////////////////////////////////////////////

void Scene::toggleWireFrame()
{
	if (input->isKeyDown('p') && !m_wireFrame)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		m_wireFrame = true;
		input->setKeyUp('p');
		brownDwarf->setWireFrameMode(true);
		planet->setWireFrameMode(true);
		planetAtmos->setWireFrameMode(true);
		moon->setWireFrameMode(true);
		moonOfMoon->setWireFrameMode(true);
		lumpOfCoal->setWireFrameMode(true);
		candle->setWireFrameMode(true);
	}

	if (input->isKeyDown('p') && m_wireFrame)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		m_wireFrame = false;
		input->setKeyUp('p');
		brownDwarf->setWireFrameMode(false);
		planet->setWireFrameMode(false);
		planetAtmos->setWireFrameMode(false);
		moon->setWireFrameMode(false);
		moonOfMoon->setWireFrameMode(false);
		lumpOfCoal->setWireFrameMode(false);
		candle->setWireFrameMode(false);
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
	displayText(-1.f, 0.96f, 1.0f, 1.0f, 1.0f, mouseText);
	displayText(-1.f, 0.90f, 1.0f, 1.0f, 1.0f, fps);
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

//////////////////////////////////////////////////////////// GENERAL SCENE STUFF END //////////////////////////////////////////////////
