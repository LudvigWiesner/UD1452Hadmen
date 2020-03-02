#pragma once
#include "Construction.h"

class Furnace : public Construction
{
private:
	bool beenPlaced;

public:
	Furnace(int sizeX, int sizeY, float xPos, float yPos, const int index, ResHandler* resourceHandler);

	bool isPlaced() const;

	// Inherited via Construction
	virtual void build(PlayerCharacter* player) override;

};