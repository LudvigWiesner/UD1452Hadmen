#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed) 
	: Entity(index, resourceHandler, nrOfRows, nrOfColumns, speed)
{
	this->sprite.setPosition(200.0f, 200.0f);
	this->selected = false;
	this->vertDir = NO;
	this->horDir = NO;
}

void PlayerCharacter::moveCharacterTo(sf::Vector2i coordinates)
{
	if (coordinates.y > this->sprite.getPosition().y)
	{
		this->vertDir = UP;
	}
	else if (coordinates.y < this->sprite.getPosition().y)
	{
		this->vertDir = DOWN;
	}
	if (coordinates.x > this->sprite.getPosition().x)
	{
		this->horDir = RIGHT;
	}
	else if (coordinates.x < this->sprite.getPosition().x)
	{
		this->horDir = LEFT;
	}

	this->sprite.move(this->horDir, this->vertDir);
}

void PlayerCharacter::setSelected(const bool set)
{
	this->selected = set;
}

bool PlayerCharacter::isSelected() const
{
	return this->selected;
}
