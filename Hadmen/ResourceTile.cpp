#include "ResourceTile.h"

ResourceTile::ResourceTile(std::string name)
{
	this->name = name;
}

int ResourceTile::getResource() const
{
	srand(unsigned int(0));
	return rand() % 1 + 3;
}
