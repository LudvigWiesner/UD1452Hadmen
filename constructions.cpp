#include "constructions.h"
#include <iostream>

void Construction::changePosValue(float xPos, float yPos)
{
	setCoordinates(xPos, yPos);
}

Construction::Construction(const int index, ResHandler* resourceHandler)
	:TileEntity(index, resourceHandler, 0,0)
{
	this->beenPlaced = false;
}

bool Construction::isSamePlace(PlayerCharacter& pc, Construction& otherConstruct, sf::RenderWindow &window, Construction &self)
{
	bool inSamePos = false;
	if (beenPlaced == false)
	{
		

		int direction = pc.getDirection();
		int xPos = 0;
		int yPos = 0;

		if (direction == 3)
		{
			xPos = pc.getPosition().x;
			yPos = pc.getPosition().y - 80;
		}
		else if (direction == 1)
		{
			xPos = pc.getPosition().x;
			yPos = pc.getPosition().y + 80;
		}
		else if (direction == 4)
		{
			xPos = pc.getPosition().x + 80;
			yPos = pc.getPosition().y;
		}
		else if (direction == 2)
		{
			xPos = pc.getPosition().x - 80;
			yPos = pc.getPosition().y;
		}


		self.changePosValue(xPos, yPos);
		window.draw(self);

		if (getBounds().intersects(otherConstruct.getBounds()))

		{
			inSamePos = true;
			//std::cout << "intersected" << std::endl;
		}
		else
		{
			inSamePos = false;
			//std::cout << "didnt intersect" << std::endl;
		}

		self.changePosValue(0, 0);

	}
	return inSamePos;
}

bool Construction::hasBeenPlaced() const
{
	return beenPlaced;
}

void Construction::changePlacedValue(int value)
{
	if (value == 1)
	{
		beenPlaced = true;
	}
	if (value == 0)
	{
		beenPlaced = false;
	}
}

sf::Vector2f Construction::checkPlayerPos(PlayerCharacter* player)
{
	return player->getPlayerPosition();
}

bool Construction::playerInRange(PlayerCharacter* pc)
{
	bool inRange = false;

	if (pc->getPlayerPosition().x - getConstructionPosition().x < 100 && pc->getPlayerPosition().x - getConstructionPosition().x > -100 &&
		pc->getPlayerPosition().y - getConstructionPosition().y < 100 && pc->getPlayerPosition().y - getConstructionPosition().y > -100)
	{
		inRange = true;
		std::cout << "Inrange of furnace" << std::endl;
	}

	return inRange;
}

sf::Vector2f Construction::getConstructionPosition()
{
	return this->getPosition();
}

void Construction::build(PlayerCharacter* player)
{
	//check if its been placed
	if (beenPlaced == false)
	{

		//check for player pos (+ check for player facing direction?)

		int xPlayerPos = checkPlayerPos(player).x;
		int yPlayerPos = checkPlayerPos(player).y;

		int direction = player->getDirection();

		std::cout << direction << std::endl;

		//set furnace pos relevant to player pos + extra
		if (direction == 3)
		{
			changePosValue(xPlayerPos, yPlayerPos - 80);
		}
		else if (direction == 1)
		{
			changePosValue(xPlayerPos, yPlayerPos + 80);
		}
		else if (direction == 4)
		{
			changePosValue(xPlayerPos + 80, yPlayerPos);
		}
		else if (direction == 2)
		{
			changePosValue(xPlayerPos - 80, yPlayerPos);
		}
		

		//set been placed to true

		changePlacedValue(1);

	}
}
