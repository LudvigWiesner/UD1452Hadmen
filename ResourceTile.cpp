#include "ResourceTile.h"

ResourceTile::ResourceTile(const int index, ResHandler* resourceHandler, std::string name, float x, float y) : TileEntity(index, resourceHandler,x,y)
{
	this->name = name;
	this->containsResource = true;
}

bool ResourceTile::getIfHasResource() const
{
	return this->containsResource;
}

int ResourceTile::getResource() const
{
	if (this->name == "Battery")
	{
		return 1;
	}
	else
	{
		srand(unsigned int(0));
		return rand() % 3 + 1;
	}
}

std::string ResourceTile::getName() const
{
	return this->name;
}

void ResourceTile::setName(std::string name)
{
	this->name = name;
}

void ResourceTile::switchTexture(ResHandler* resourceHandler)
{
	if (this->name == "Aluminium Deposit" || this->name == "Coal Deposit" || this->name == "Iron Deposit" || this->name == "Stone Deposit")
	{
		this->setTexture(12, resourceHandler);
		this->containsResource = false;
	}
	else if (this->name == "Tree")
	{
		this->setTexture(26, resourceHandler);
		this->containsResource = false;
	}
	else if (this->name == "Water")
	{
		this->setTexture(13, resourceHandler);
		this->containsResource = false;
	}
	else if (this->name == "Poisoned Water")
	{
		this->setTexture(8, resourceHandler);
	}
	else if (this->name == "Battery")
	{
		this->setTexture(13, resourceHandler);
	}
}
