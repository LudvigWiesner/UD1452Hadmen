#include "Weapon.h"

Weapon::Weapon(const int index, ResHandler* resourceHandler, std::string name, int damage, int accuracy, int nrOfRows, int nrOfColumns) : Item(index, resourceHandler, name)
{
	this->damage = damage;
	this->accuracy = accuracy;
	this->intRect = sf::IntRect(0, 0, this->texture.getSize().x / nrOfRows, this->texture.getSize().y);
	this->sprite.setTextureRect(this->intRect);
	this->timeCounter = 0;
	this->updateTime = 30;
	this->frameCounter = 0;
	this->running = false;
}

void Weapon::startAnimation()
{
	this->running = true;
}

void Weapon::Animate()
{
	if (running)
	{
		this->timeCounter = (this->timeCounter + 1) % this->updateTime;
		if (this->timeCounter == 0)
		{
			this->intRect.left = (this->intRect.left + this->intRect.width) % (int)this->texture.getSize().x;
		}
		this->sprite.setTextureRect(this->intRect);
		this->frameCounter++;
	}
	if (frameCounter == 2)
	{
		running = false;
		this->resetCounter();
	}
}

void Weapon::mapPosition(PlayerCharacter* PC)
{
	this->sprite.setPosition(PC->getPosition().x, PC->getPosition().y);
}

void Weapon::resetCounter()
{
	this->frameCounter = 0;
}
