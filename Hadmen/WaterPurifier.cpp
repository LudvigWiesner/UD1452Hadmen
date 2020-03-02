#include "WaterPurifier.h"

WaterPurifier::WaterPurifier(int sizeX, int sizeY, float xPos, float yPos, const int index, ResHandler* resourceHandler)
	:Construction(sizeX, sizeY, xPos, yPos, index, resourceHandler)
{
	this->beenPlaced = false;
}

bool WaterPurifier::isPlaced() const
{
	return beenPlaced;
}

void WaterPurifier::build(PlayerCharacter* player)
{
	//check if its been placed
	if (beenPlaced == false)
	{

		//check for player pos (+ check for player facing direction?)

		float xPlayerPos = checkPlayerPos(player).x;
		float yPlayerPos = checkPlayerPos(player).y;

		//set furnace pos relevant to player pos + extra

		changePosValue(xPlayerPos - 80, yPlayerPos - 80);

		//set been placed to true

		beenPlaced = true;

	}
}
