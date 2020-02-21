#pragma once
#ifndef ITEM_H
#define ITEM_H
#include "Clickable.h"

class Item : public Clickable
{
private:
	std::string name;
	int nrOfItem;
public:
	Item(const int index, ResHandler* resourceHandler, std::string name);

	int getNrOfItem()const;
	void removeNrOfItem(const int nrToRemove);
};
#endif // !ITEM_H
#pragma once
