#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include "PlayerCharacter.h"

class Weapon : public Item
{
private:
	int damage;
public:
	Weapon(const int index, ResHandler* resourceHandler, std::string name, int damage);
	int getDamage()const;
};
#endif // !TOOL_H

