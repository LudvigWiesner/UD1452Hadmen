#include "Furnace.h"

Furnace::Furnace(int sizeX, int sizeY, float xPos, float yPos, const int index, ResHandler* resourceHandler)
	:Construction(sizeX, sizeY,xPos, yPos, index, resourceHandler)
{
	this->beenPlaced = false;
}

bool Furnace::isPlaced() const
{
	return beenPlaced;
}

void Furnace::build(PlayerCharacter* player)
{
	//check if its been placed
	if (beenPlaced == false)
	{

		//check for player pos (+ check for player facing direction?)

		int xPlayerPos = checkPlayerPos(player).x;
		int yPlayerPos = checkPlayerPos(player).y;

		//set furnace pos relevant to player pos + extra

		changePosValue(xPlayerPos - 50, yPlayerPos - 50);

		//set been placed to true

		beenPlaced = true;

	}


}
