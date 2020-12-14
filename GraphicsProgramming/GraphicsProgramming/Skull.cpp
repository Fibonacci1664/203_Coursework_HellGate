#include "Skull.h"

Skull::Skull()
{
	initSkull();
}

Skull::~Skull()
{

}

void Skull::render()
{
	skull->render();
}

void Skull::initSkull()
{
	skull = new Model();
	skull->load(skullFilePath, skullTexPath);
}
