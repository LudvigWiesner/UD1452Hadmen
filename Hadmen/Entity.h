#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include "Clickable.h"
#include "MoveDirections.h"
#include <ctime>

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
	void switchSprite(const int row);


	bool alive;
	int MaxHP;
	int currentHP;
	int evasion;
public:
	Entity(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed = 3.0F);
	Entity(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, int evasion, float speed = 3.0F);
	void moveEntityTo(sf::Vector2f coordinates);
	void moveEntityTo(sf::Vector2f coordinates, const int row);

	void takeDamage(const int damage);
	void makeAttack(Entity& otherEntity, const int damage);

	void setEvasion(const int evasion);
	void increaseMaxHP(const int healthToAdd);
	void healCurrentHP(const int healthToHeal);

	int getMaxHP()const;
	int getCurrentHP()const;
	
};
#endif // !ENTITY_H
