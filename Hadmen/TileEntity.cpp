#include "TileEntity.h"

TileEntity::TileEntity()
{
	this->tileTexture.loadFromFile("../Images/floor01.png");
	this->tileSprite.setTexture(tileTexture);
}

TileEntity::TileEntity(const int index, ResHandler *resourceHandler)
{
	this->tileTexture = resourceHandler->getTexture(index);
	this->tileSprite.setTexture(tileTexture);
}

TileEntity::~TileEntity()
{
}

void TileEntity::setCoordinates(float xPos,float yPos)
{
	this->tileSprite.move(xPos,yPos);
}

void TileEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->tileSprite);
}
