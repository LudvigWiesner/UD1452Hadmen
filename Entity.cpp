#include "Entity.h"

Entity::Entity(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed) : Clickable(index, resourceHandler)
{
	this->horDir = NO;
	this->vertDir = NO;
	this->speed = speed;
	this->intRect = sf::IntRect(0, 0, this->getTextureSize().x / nrOfColumns, this->getTextureSize().y / nrOfRows);
	this->setTextureRect(this->intRect);
	this->timeCounter = 0;
	this->updateTime = 30;
	this->alive = true;
	this->MaxHP = 100;
	this->currentHP = 100;
	this->evasion = 0;
	this->setOrigin(intRect.left / nrOfColumns, intRect.top / nrOfRows);
}

Entity::Entity(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, int evasion, float speed) : Clickable(index, resourceHandler)
{
	this->horDir = NO;
	this->vertDir = NO;
	this->speed = speed;
	this->intRect = sf::IntRect(0, 0, this->getTextureSize().x / nrOfColumns, this->getTextureSize().y / nrOfRows);
	this->setTextureRect(this->intRect);
	this->timeCounter = 0;
	this->updateTime = 30;
	this->alive = true;
	this->MaxHP = 100;
	this->currentHP = 100;
	this->setEvasion(evasion);
	this->setOrigin(intRect.left / nrOfColumns, intRect.top / nrOfRows);
}

void Entity::moveEntityTo(sf::Vector2f coordinates)
{
	this->horDir = NO;
	this->vertDir = NO;
	if (coordinates.y > this->getPosition().y + this->getBounds().height / 2)
	{
		this->vertDir = UP;
	}
	else if (coordinates.y < this->getPosition().y)
	{
		this->vertDir = DOWN;
	}
	if (coordinates.x > this->getPosition().x + this->getBounds().width / 2)
	{
		this->horDir = RIGHT;
	}
	else if (coordinates.x < this->getPosition().x)
	{
		this->horDir = LEFT;
	}
	this->moveSprite(this->horDir, this->vertDir, this->speed);
	this->switchSprite();
}

void Entity::moveEntityTo(sf::Vector2f coordinates, const int row)
{
	if (row != 1)
	{
		this->horDir = NO;
		this->vertDir = NO;
		if (coordinates.y > this->getPosition().y)
		{
			this->vertDir = UP;
		}
		else if (coordinates.y < this->getPosition().y)
		{
			this->vertDir = DOWN;
		}
		if (coordinates.x > this->getPosition().x)
		{
			this->horDir = RIGHT;
		}
		else if (coordinates.x < this->getPosition().x)
		{
			this->horDir = LEFT;
		}
		this->moveSprite(this->horDir, this->vertDir, this->speed);
		this->switchSprite(row);
	}
	else
	{
		this->switchSprite(row);
	}
}

void Entity::switchSprite()
{
	if (this->vertDir == UP)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::DOWN);
		this->direction = 1;
	}
	else if (this->vertDir == DOWN)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::UP);
		this->direction = 3;
	}
	if (this->horDir == LEFT && vertDir == NO)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::LEFT);
		this->direction = 2;
	}
	else if (this->horDir == RIGHT && vertDir == NO)
	{
		this->intRect.top = this->intRect.height * (int)(MoveDirections::RIGHT);
		this->direction = 4;
	}

	this->timeCounter = (this->timeCounter + 1) % this->updateTime;
	if (this->timeCounter == 0)
	{
		this->intRect.left = (this->intRect.left + this->intRect.width) % (int)this->getTextureSize().x;
	}
	this->setTextureRect(this->intRect);
}

void Entity::switchSprite(const int row)
{
	this->intRect.top = row * this->intRect.height;
	this->timeCounter = (this->timeCounter + 1) % this->updateTime;
	if (this->timeCounter == 0)
	{
		this->intRect.left = (this->intRect.left + this->intRect.width) % (int)this->getTextureSize().x;
	}
	this->setTextureRect(this->intRect);
}

void Entity::takeDamage(const int damage)
{
	srand(unsigned int(0));
	int toHit = rand() % 100 + 1;

	if (toHit > this->evasion)
	{
		this->currentHP -= damage;
		if (this->currentHP <= 0)
		{
			this->alive = false;
		}
	}
}

void Entity::makeAttack(Entity& otherEntity, const int damage)
{
	otherEntity.takeDamage(damage);
}

void Entity::setEvasion(const int evasion)
{
	this->evasion = evasion;
}

void Entity::increaseMaxHP(const int healthToAdd)
{
	this->MaxHP += healthToAdd;
}

void Entity::healCurrentHP(const int healthToHeal)
{
	if (this->currentHP < this->MaxHP)
	{
		this->currentHP += healthToHeal;
	}
}

int Entity::getMaxHP() const
{
	return this->MaxHP;
}

int Entity::getCurrentHP() const
{
	return this->currentHP;
}

int Entity::getDirection() const
{
	return direction;
}




