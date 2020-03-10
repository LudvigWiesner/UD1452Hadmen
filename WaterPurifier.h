#pragma once
#include "Construction.h"

class WaterPurifier : public Construction
{
private:
	int xPos;
	int yPos;
	int range;
	int topLeftX;
	int topRightX;
	int bottomLeftX;
	int bottomRightX;
	int topLeftY;
	int topRightY;
	int bottomLeftY;
	int bottomRightY;

public:
	WaterPurifier(const int index, ResHandler* resourceHandler);

	void setPositions();

	void setFourPoints(int arr[]);

	void checkIfPoisioned();

};