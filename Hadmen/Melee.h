#pragma once
#include "Entity.h"
#include "PlayerCharacter.h"
#include <string>
#include <iostream>
#include <cmath>
#include <math.h>


class Melee :public	Entity
{
private:
	std::string name;
	int hp;
	int atk;

	bool playerDetector;
public:
	Melee(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, std::string monsterName,float posX,float posY, float speed = 3.0F,int hp=10,int atk=1 );
	virtual ~Melee();

	void ifPlayerDetected(PlayerCharacter *player);

};