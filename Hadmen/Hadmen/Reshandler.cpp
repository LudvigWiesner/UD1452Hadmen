#include "Reshandler.h"

ResHandler::ResHandler()
{
	this->textures = new sf::Texture[this->size];
	this->textures[0].loadFromFile("../Images/AluminiumTexture.png");
	this->textures[1].loadFromFile("../Images/CoalTexture.png");
	this->textures[2].loadFromFile("../Images/IronTexture.png");
	this->textures[3].loadFromFile("../Images/BaseImage.png");
	this->textures[4].loadFromFile("../Images/floor01.png");
	this->textures[5].loadFromFile("../Images/StoneTexture.png");
	this->textures[6].loadFromFile("../Images/TreeTexture.jpg");
	this->textures[7].loadFromFile("../Images/wall01.png");
	this->textures[8].loadFromFile("../Images/WaterTexture.jpg");
	this->textures[9].loadFromFile("../Images/backgroundImage.jpg");
}

ResHandler::~ResHandler()
{
	delete[]this->textures;
}

sf::Texture ResHandler::getTexture(const int index)
{
	return this->textures[index];
}
