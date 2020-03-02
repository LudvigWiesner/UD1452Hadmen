#include "Weapon.h"

Weapon::Weapon(const int index, ResHandler* resourceHandler, std::string name, int damage) : Item(index, resourceHandler, name)
{
	this->damage = damage;
}

int Weapon::getDamage() const
{
	return this->damage;
}
