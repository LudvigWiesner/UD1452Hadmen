#include "ResourceTile.h"

ResourceTile::ResourceTile(const int index, ResHandler* resourceHandler, std::string name,int x,int y) : TileEntity(index, resourceHandler,x,y)
{
	this->name = name;
}

int ResourceTile::getResource() const
{
	srand(unsigned int(0));
	return rand() % 1 + 3;
}

std::string ResourceTile::getName() const
{
	return this->name;
}
