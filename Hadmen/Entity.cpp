#include "Entity.h"

Entity::Entity(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed) : Clickable(index, resourceHandler)
{
	this->speed = speed;
	this->intRect = sf::IntRect(0, 0, this->texture.getSize().x / nrOfColumns, this->texture.getSize().y / nrOfRows);
	this->sprite.setTextureRect(this->intRect);
	this->timeCounter = 0;
	this->updateTime = 30;
}

void Entity::move(MoveDirections moveDirection)
{
	if (moveDirection == MoveDirections::DOWN)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::DOWN);
		this->sprite.move(0.0f, this->speed);
	}
	else if (moveDirection == MoveDirections::LEFT)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::LEFT);
		this->sprite.move(-this->speed, 0.0f);
	}
	else if (moveDirection == MoveDirections::RIGHT)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::RIGHT);
		this->sprite.move(this->speed, 0.0f);
	}
	else if (moveDirection == MoveDirections::UP)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::UP);
		this->sprite.move(0.0f, -this->speed);
	}

	this->timeCounter = (this->timeCounter + 1) % this->updateTime;
	if (this->timeCounter == 0)
	{
		this->intRect.left = (this->intRect.left + this->intRect.width) % (int)this->texture.getSize().x;
	}
	this->sprite.setTextureRect(this->intRect);
}
