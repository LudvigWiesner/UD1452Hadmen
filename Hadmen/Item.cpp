#include "Item.h"

Item::Item(const int index, ResHandler* resourceHandler, std::string name) : Clickable(index, resourceHandler)
{
	this->name = name;
	this->nrOfItem = 0;
}

int Item::getNrOfItem() const
{
	return this->nrOfItem;
}

void Item::removeNrOfItem(const int nrToRemove)
{
	if (this->nrOfItem < nrToRemove)
	{
		this->nrOfItem = 0;
	}
	else
	{
		this->nrOfItem = this->nrOfItem - nrToRemove;
	}
}
