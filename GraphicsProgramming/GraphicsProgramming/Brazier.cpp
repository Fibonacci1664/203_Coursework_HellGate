#include "Brazier.h"


#include "DragonPortal.h"

Brazier::Brazier()
{
	initBrazier();
}

Brazier::~Brazier()
{

}

void Brazier::render()
{
	brazier->render();
}

void Brazier::initBrazier()
{
	brazier = new Model();
	brazier->load(brazierFilePath, brazierTexPath);
}