#include "Furnace.h"
#include <iostream>


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
		std::cout << "added coal" << std::endl;
	}
}

void Furnace::proccessCoal()
{
	if (this->coal > 0)
	{
		this->counter++;
		std::cout << "Proccessing" << std::endl;
		if (counter == updateTime)
		{
			std::cout << "One coal got used" << std::endl;
			this->coal -= 1;
			this->counter = 0;
		}
	}
}



void Furnace::updateFurnace(ResHandler* resourceHandler)
{
	if (this->coal > 0)
	{
		this->updateSprite(26, resourceHandler);
	}
	if (this->coal == 0)
	{
		this->updateSprite(29, resourceHandler);
	}
}
