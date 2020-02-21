#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include "PlayerCharacter.h"

class Weapon : public Item
{
private:
	int damage;
	int accuracy;

	sf::IntRect intRect;
	int timeCounter;
	int updateTime;
	int frameCounter;

	bool running;
	
	void resetCounter();

public:
	Weapon(const int index, ResHandler* resourceHandler, std::string name, int damage, int accuracy, int nrOfRows, int nrOfColumns);
	void startAnimation();
	void Animate();
	void mapPosition(PlayerCharacter* PC);
};
#endif // !TOOL_H

