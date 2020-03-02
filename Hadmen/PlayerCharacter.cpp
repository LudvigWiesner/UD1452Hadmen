#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed) 
	: Entity(index, resourceHandler, nrOfRows, nrOfColumns, speed)
{
	this->setCoordinates(200.0f, 200.0f);
	this->selected = false;

	this->equippedWeapon = nullptr;
	this->inventory = new List<Item>;

	this->stamina = 100;
	this->melee = 1;
	this->ranged = 1;
	this->woodcutting = 1;
	this->mining = 1;
	this->hunting = 1;
	this->engineering = 1;
	this->cooking = 1;
	this->construction = 1;
}

PlayerCharacter::~PlayerCharacter()
{
	delete this->inventory;
	delete this->equippedWeapon;
}

void PlayerCharacter::setSelected(const bool set)
{
	this->selected = set;
}

bool PlayerCharacter::isSelected() const
{
	return this->selected;
}

sf::Vector2f PlayerCharacter::getPlayerPosition() const
{
	return this->getPosition();
}

void PlayerCharacter::addItem(const Item itemToAdd)
{
	this->inventory->insertAt(this->inventory->length(), itemToAdd);
}

void PlayerCharacter::removeItem(const Item itemToRemove)
{
	this->inventory->removeElement(itemToRemove);
}

int PlayerCharacter::getNrOfAnItem(const Item itemToCount)
{
	int index = this->inventory->findElement(itemToCount);
	return this->inventory->getAt(index).getNrOfItem();
}

int PlayerCharacter::getNrOfItems() const
{
	return this->inventory->length();
}

void PlayerCharacter::getAllItems(Item arr[])
{
	this->inventory->getAll(arr, this->inventory->length());
}

int PlayerCharacter::getEquippedWeaponDamage() const
{
	return this->equippedWeapon->getDamage();
}

void PlayerCharacter::equipWeapon(const Item itemToEquip)
{
	if (this->equippedWeapon != nullptr)
	{
		delete this->equippedWeapon;
	}
	this->equippedWeapon = new Item(itemToEquip);
}

void PlayerCharacter::addExp(std::string attribute, float expToAdd)
{
	if (attribute == "Melee")
	{
		this->melee += expToAdd;
	}
	else if (attribute == "Ranged")
	{
		this->ranged += expToAdd;
	}
	else if (attribute == "Woodcutting")
	{
		this->woodcutting += expToAdd;
	}
	else if (attribute == "Mining")
	{
		this->mining += expToAdd;
	}
	else if (attribute == "Hunting")
	{
		this->hunting += expToAdd;
	}
	else if (attribute == "Engineering")
	{
		this->engineering += expToAdd;
	}
	else if (attribute == "Construction")
	{
		this->construction += expToAdd;
	}
}

int PlayerCharacter::getMeleeLevel() const
{
	return static_cast<int>(this->melee);
}

int PlayerCharacter::getRangedLevel() const
{
	return static_cast<int>(this->ranged);
}

int PlayerCharacter::getWoodcuttingLevel() const
{
	return static_cast<int>(this->woodcutting);
}

int PlayerCharacter::getMiningLevel() const
{
	return static_cast<int>(this->mining);
}

int PlayerCharacter::getHuntingLevel() const
{
	return static_cast<int>(this->hunting);
}

int PlayerCharacter::getEngineeringLevel() const
{
	return static_cast<int>(this->engineering);
}

int PlayerCharacter::getConstructionLevel() const
{
	return static_cast<int>(this->construction);
}
