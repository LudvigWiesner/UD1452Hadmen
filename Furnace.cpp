#include "Furnace.h"

Furnace::Furnace(const int index, ResHandler* resourceHandler)
	:Construction(index, resourceHandler)
{
	this->coal = 0;
	this->updateTime = 600;
	this->counter = 0;
}

void Furnace::addCoal(PlayerCharacter* pc)
{
	if (playerInRange(pc) == true)
	{
		this->coal += 5;
	}
}

void Furnace::proccessCoal()
{
	if (this->coal > 0)
	{
		this->counter++;
		if (counter == updateTime)
		{
			this->coal -= 1;
			this->counter = 0;
		}
	}
}



void Furnace::updateFurnace(ResHandler* resourceHandler)
{
	if (this->coal > 0)
	{
		this->setTexture(35, resourceHandler);
		//this->updateSprite(35, resourceHandler);
	}
	if (this->coal == 0)
	{
		this->setTexture(29, resourceHandler);
		//this->updateSprite(29, resourceHandler);
	}
}

int Furnace::getCoalAmount() const
{
	return this->coal;
}
