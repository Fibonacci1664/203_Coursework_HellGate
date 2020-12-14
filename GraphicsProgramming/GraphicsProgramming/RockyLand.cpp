#include "RockyLand.h"

RockyLand::RockyLand()
{
	initRockyLand();
}

RockyLand::~RockyLand()
{

}

void RockyLand::render()
{
	rockyLand->render();
}

void RockyLand::initRockyLand()
{
	rockyLand = new Model();
	rockyLand->load(rockyLandFilePath, rockyLandTexPath);
}