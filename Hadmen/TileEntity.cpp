#include "TileEntity.h"

TileEntity::TileEntity()
{
	this->tileTexture.loadFromFile("../Images/floor01.png");
	this->tileSprite.setTexture(tileTexture);
	//this->collision = true;
}

TileEntity::TileEntity(const std::string filename)
{
	this->tileTexture.loadFromFile("../Images/" + filename);
	this->tileSprite.setTexture(tileTexture);
	//this->collision = false;

	//if (filename == "wall01.png")
	//{
	//	this->collision = true;
	//}

}

TileEntity::~TileEntity()
{
}

//bool TileEntity::collision()
//{
//	return this->collision;
//}
//
//void TileEntity::setCollision(bool state)
//{
//	this->collision = state;
//}

void TileEntity::setCoordinates(float xPos,float yPos)
{
	this->tileSprite.move(xPos,yPos);
}

void TileEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->tileSprite);
}
