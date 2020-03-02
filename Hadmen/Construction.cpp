#include "Construction.h"

void Construction::changePosValue(float xPos, float yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}

Construction::Construction(int sizeX, int sizeY, float xPos, float yPos, const int index, ResHandler* resourceHandler)
	:TileEntity(index, resourceHandler, 0,0)
{

}

sf::Vector2f Construction::checkPlayerPos(PlayerCharacter* player)
{
	return player->getPlayerPosition();
}

bool Construction::playerInRange()
{
	bool inRange = false;

	if (pc->getPlayerPosition().x - getConstructionPosition().x < 100 && pc->getPlayerPosition().x - getConstructionPosition().x > -100 &&
		pc->getPlayerPosition().y - getConstructionPosition().y < 100 && pc->getPlayerPosition().y - getConstructionPosition().y > -100)
	{
		inRange = true;
	}

	return inRange;
}

sf::Vector2f Construction::getConstructionPosition()
{
	return this->getPosition();
}
