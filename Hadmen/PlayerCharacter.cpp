#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed) 
	: Entity(index, resourceHandler, nrOfRows, nrOfColumns, speed)
{
	this->setCoordinates(200.0f, 200.0f);
	this->selected = false;
}

void PlayerCharacter::setSelected(const bool set)
{
	this->selected = set;
}

bool PlayerCharacter::isSelected() const
{
	return this->selected;
}

sf::Vector2f PlayerCharacter::getPlayerPosition() const
{
	return this->getPosition();
}
