#include "ItemHandler.h"

ItemHandler::ItemHandler(ResHandler* resourceHandler)
{
	this->nrOfItems = 8;
	this->itemSize = 100;
	this->items = new Item*[itemSize];
	this->items[0] = new Item(0, resourceHandler, "Aluminium Ore");
	this->items[1] = new Item(22, resourceHandler, "Coal");
	this->items[2] = new Item(2, resourceHandler, "Iron Ore");
	this->items[3] = new Item(5, resourceHandler, "Stone Ore");
	this->items[4] = new Item(20, resourceHandler, "Iron Bar");
	this->items[5] = new Item(21, resourceHandler, "Aluminium Bar");
	this->items[6] = new Item(23, resourceHandler, "Stone Block");
	this->items[7] = new Item(16, resourceHandler, "Sword", 1, 5);
}

ItemHandler::~ItemHandler()
{
	for (int i = 0; i < this->nrOfItems; i++)
	{
		delete this->items[i];
	}
	delete[]this->items;
}

Item ItemHandler::getItem(const int index)
{
	return *this->items[index];
}

