#pragma once
#include "TileEntity.h"
#include "PlayerCharacter.h"

class Construction: public TileEntity
{
private:
	int sizeX;
	int sizeY;
	float yPos;
	float xPos;

	PlayerCharacter* pc;

protected:
	void changePosValue(float xPos, float yPos);

public:
	Construction(int sizeX, int sizeY, float xPos, float yPos, const int index, ResHandler* resourceHandler);


	sf::Vector2f checkPlayerPos(PlayerCharacter* player);

	bool playerInRange();
	sf::Vector2f getConstructionPosition();
	virtual void build(PlayerCharacter* player) = 0;

};