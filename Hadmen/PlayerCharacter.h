#pragma once
#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "Entity.h"
#include "List.h"

class PlayerCharacter : public Entity
{
private:
	bool selected;
public:
	PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed = 3.0F);

	void setSelected(const bool set);
	bool isSelected()const;
	sf::Vector2f getPlayerPosition()const;
};
#endif // !CHARACTER_H
