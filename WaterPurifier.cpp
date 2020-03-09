#include "WaterPurifier.h"

WaterPurifier::WaterPurifier( const int index, ResHandler* resourceHandler)
	:Construction(index, resourceHandler)
{
	this->range = 200;
	this->xPos = 0;
	this->yPos = 0;
	this->topLeftX = 0;
	this->topRightX = 0;
	this->bottomLeftX = 0;
	this->bottomRightX = 0;
	this->topLeftY = 0;
	this->topRightY = 0;
	this->bottomLeftY = 0;
	this->bottomRightY = 0;
}

void WaterPurifier::setPositions()
{
	this->xPos = getPosition().x;
	this->yPos = getPosition().y;
	this->topLeftX = xPos - 100;
	this->topLeftY = yPos - 100;
	this->topRightX = xPos + 100;
	this->topRightY = yPos - 100;
	this->bottomLeftX = xPos - 100;
	this->bottomLeftY = yPos + 100;
	this->bottomRightX = xPos + 100;
	this->bottomRightY = yPos + 100;
}

void WaterPurifier::setFourPoints(int arr[])
{
	arr[0] = topLeftX;
	arr[1] = topRightX;
	arr[2] = topLeftY;
	arr[3] = bottomLeftY;
}

void WaterPurifier::checkIfPoisioned()
{
	for (int y = topLeftY; y < bottomLeftY; y++)
	{
		for (int x = topLeftX; x < topRightX; x++)
		{
			if ()
			{

			}
		}
	}
}


