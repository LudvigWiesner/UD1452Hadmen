#pragma once
#include "TileEntity.h"
#include "PlayerCharacter.h"

class Construction : public TileEntity
{
private:
	bool beenPlaced;

protected:
	void changePosValue(float xPos, float yPos);

public:
	Construction(const int index, ResHandler* resourceHandler);

	bool isSamePlace(PlayerCharacter& pc, Construction& otherConstruct, sf::RenderWindow &window, Construction &self);
	bool hasBeenPlaced() const;
	void changePlacedValue(int value);
	sf::Vector2f checkPlayerPos(PlayerCharacter* player);

	bool playerInRange(PlayerCharacter* pc);
	sf::Vector2f getConstructionPosition();
	void build(PlayerCharacter* player);

};