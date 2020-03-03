#include "Item.h"

Item::Item() : Clickable()
{
	this->name = "";
	this->nrOfItem = 0;
	this->damage = 0;
}

Item::Item(const int index, ResHandler* resourceHandler, std::string name, int nrOfItem, int damage) : Clickable(index, resourceHandler)
{
	this->name = name;
	this->nrOfItem = nrOfItem;
	this->damage = damage;
}

Item::Item(const Item& otherItem) : Clickable(otherItem)
{
	this->name = otherItem.name;
	this->nrOfItem = otherItem.nrOfItem;
	this->damage = otherItem.damage;
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
		this->nrOfItem -= nrToRemove;
	}
}

void Item::addNrOfItem(const int nrToAdd)
{
	this->nrOfItem += nrToAdd;
}

int Item::getDamage() const
{
	return this->damage;
}

std::string Item::getName() const
{
	return this->name;
}

bool Item::operator==(const Item& otherItem)
{
	return this->name == otherItem.name;
}
