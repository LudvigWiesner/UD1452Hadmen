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
public:
	Item();
	Item(const int index, ResHandler* resourceHandler, std::string name, int damage);

	int getNrOfItem()const;
	void removeNrOfItem(const int nrToRemove);
	void addNrOfItem(const int nrToAdd);
	int getDamage()const;
	std::string getName()const;

	bool operator==(const Item& otherItem);
};
#endif // !ITEM_H
#pragma once
