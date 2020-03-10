#pragma once
#ifndef ITEMHANDLER_H
#define ITEMHANDLER_H
#include "Item.h"
#include "Reshandler.h"

class ItemHandler
{
private:
	Item** items;
	int itemSize;
	int nrOfItems;
public:
	ItemHandler(ResHandler* resourceHandler);
	~ItemHandler();

	Item getItem(const int index);
};
#endif // !ITEMHANDLER_H
