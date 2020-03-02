#pragma once
#include "Construction.h"

class WaterPurifier : public Construction
{
private:
	bool beenPlaced;
public:
	WaterPurifier(int sizeX, int sizeY, float xPos, float yPos, const int index, ResHandler* resourceHandler);

	bool isPlaced() const;

	// Inherited via Construction
	virtual void build(PlayerCharacter* player) override;
};