#pragma once
#ifndef ITEM_H
#define ITEM_H
#include "Clickable.h"

class Item : public Clickable
{
private:
	std::string name;
	int nrOfItem;
	int damage;
	bool weaponTag;
public:
	Item();
	Item(const int index, ResHandler* resourceHandler, std::string name, int nrOfItem = 1, int damage = 0);
	Item(const int index, ResHandler* resourceHandler, std::string name, bool weapon, int nrOfItem = 1, int damage = 0);
	Item(const Item& otherItem);

	int getNrOfItem()const;
	void removeNrOfItem(const int nrToRemove);
	void addNrOfItem(const int nrToAdd);
	int getDamage()const;
	std::string getName()const;
	bool getIfWeapon()const;

	bool operator==(const Item& otherItem);
};
#endif // !ITEM_H
#pragma once
