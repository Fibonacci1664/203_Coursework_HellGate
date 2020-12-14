#include "DragonPortal.h"

DragonPortal::DragonPortal()
{
	initDragonPortal();
}

DragonPortal::~DragonPortal()
{

}

void DragonPortal::render()
{
	dragonPortal->render();
}

void DragonPortal::initDragonPortal()
{
	dragonPortal = new Model();
	dragonPortal->load(dragonPortalFilePath, dragonPortalTexPath);
}