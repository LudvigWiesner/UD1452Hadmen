#pragma once
#include "Entity.h"
#include "PlayerCharacter.h"
#include <cmath>
#include <math.h>
#include <iostream>


class Ranged :public	Entity
{
private:
	std::string name;
	sf::Time attackCD;
	sf::Time tgtChangeCD;

	int atk;
	int detectRNG;
	int atkRNG;

	PlayerCharacter* target;

	bool playerDetector;
	bool atkFlag;
	bool tgtChangeFlag;
public:
	Ranged(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns,
		std::string monsterName, float posX, float posY, float speed = 2.0F, int hp = 10, int atk = 1);
	virtual ~Ranged();

	bool ifPlayerDetected(PlayerCharacter* player);
	void attack(PlayerCharacter* player);
	PlayerCharacter* targetSelection(PlayerCharacter* player1, PlayerCharacter* player2); // bör ändra till en array av player character/target
	void atkCounter(sf::Time elapstime);
	void targetChangeCD(sf::Time elapstime);

};