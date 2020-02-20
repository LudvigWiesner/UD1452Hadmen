#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "Clickable.h"
#include "MoveDirections.h"

class Entity : public Clickable
{
public:
const int LEFT = -1;
const int DOWN = -1;
const int UP = 1;
const int RIGHT = 1;
const int NO = 0;
private:
	sf::IntRect intRect;
	float speed;
	int timeCounter;
	int updateTime;

	int horDir;
	int vertDir;

	void switchSprite();
public:
	Entity(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed = 3.0F);
	void moveEntityTo(sf::Vector2i coordinates);
	
};
#endif // !ENTITY_H
