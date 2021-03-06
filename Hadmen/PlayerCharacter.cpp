#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed) 
	: Entity(index, resourceHandler, nrOfRows, nrOfColumns, speed)
{
	this->setCoordinates(200.0f, 200.0f);
	this->selected = false;

	this->equippedWeapon = nullptr;
	this->inventory = new List<Item*>;

	this->baseLevel = 1;
	this->baseExp = 0;
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
	for (int i = 0; i < this->inventory->length(); i++)
	{
		delete this->inventory->getAt(i);
	}
	delete this->inventory;
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
	bool found = false;
	int index = 0;

	for (int i = 0; i < this->inventory->length();i++)
	{
		if (this->inventory->getAt(i)->getName() == itemToAdd.getName())
		{
			found = true;
			index = i;
			i = this->inventory->length();
		}
	}
	if (found)
	{
		this->inventory->getAt(index)->addNrOfItem(itemToAdd.getNrOfItem());
	}
	else
	{
		Item* temp = new Item(itemToAdd);
		this->inventory->insertAt(this->inventory->length(), temp);
	}

}

void PlayerCharacter::removeItem(Item* itemToRemove)
{
	int index = -1;
	for (int i = 0; i < this->inventory->length(); i++)
	{
		if (this->inventory->getAt(i)->getName() == itemToRemove->getName())
		{
			index = i;
			i = this->inventory->length();
		}
	}
	if (index != -1)
	{
		delete this->inventory->getAt(index); // causes memory leaks
		this->inventory->removeAt(index);
	}
	
}

void PlayerCharacter::removeItem(const std::string itemName)
{
	int index = -1;
	for (int i = 0; i < this->inventory->length();i++)
	{
		if (this->inventory->getAt(i)->getName() == itemName)
		{
			index = i;
			i = this->inventory->length();
		}
	}
	if (index != -1)
	{
		delete this->inventory->getAt(index);
		this->inventory->removeAt(index);
	}
}

int PlayerCharacter::getNrOfAnItem(Item* itemToCount)
{
	int index = -1;
	for (int i = 0; i < this->inventory->length(); i++)
	{
		if (this->inventory->getAt(i)->getName() == itemToCount->getName())
		{
			index = i;
			i = this->inventory->length();
		}
	}
	if (index != -1)
	{
		return this->inventory->getAt(index)->getNrOfItem();
	}
	else
	{
		return index;
	}
}

int PlayerCharacter::getNrOfAnItem(const int index)
{
	return this->inventory->getAt(index)->getNrOfItem();
}

int PlayerCharacter::getNrOfAnItem(const std::string itemName)
{
	int index = -1;
	for (int i = 0; i < this->inventory->length(); i++)
	{
		if (this->inventory->getAt(i)->getName() == itemName)
		{
			index = i;
			i = this->inventory->length();
		}
	}
	if (index != -1)
	{
		return this->inventory->getAt(index)->getNrOfItem();
	}
	else
	{
		return index;
	}
}

int PlayerCharacter::getNrOfItems() const
{
	return this->inventory->length();
}

void PlayerCharacter::getAllItems(Item* arr[])
{
	this->inventory->getAll(arr, this->inventory->length());
}

void PlayerCharacter::addNrToAnItem(Item* itemToAddTo, const int nr)
{
	for (int i = 0; i < this->inventory->length(); i++)
	{
		if (this->inventory->getAt(i)->getName() == itemToAddTo->getName())
		{
			this->inventory->getAt(i)->addNrOfItem(nr);
			i = this->inventory->length();
		}
	}
}

void PlayerCharacter::removeNrFromAnItem(Item* itemToRemoveFrom, const int nr)
{
	for (int i = 0; i < this->inventory->length(); i++)
	{
		if (this->inventory->getAt(i)->getName() == itemToRemoveFrom->getName())
		{
			this->inventory->getAt(i)->removeNrOfItem(nr);
		}
	}
}

void PlayerCharacter::removeNrFromAnItem(const std::string itemName, const int nr)
{
	for (int i = 0; i < this->inventory->length(); i++)
	{
		if (this->inventory->getAt(i)->getName() == itemName)
		{
			this->inventory->getAt(i)->removeNrOfItem(nr);
			i = this->inventory->length();
			//if (this->inventory->getAt(i)->getNrOfItem() >= nr)
			//{
			//	delete this->inventory->getAt(i); 
			//	this->inventory->removeAt(i);
			//}
			//else
			//{
			//	this->inventory->getAt(i)->removeNrOfItem(nr);
			//}
		}
	}
}

int PlayerCharacter::getEquippedWeaponDamage() const
{
	return this->equippedWeapon->getDamage();
}

void PlayerCharacter::equipWeapon(Item* itemToEquip)
{
	this->equippedWeapon = itemToEquip;
}

Item* PlayerCharacter::getEquippedWeapon() const
{
	return this->equippedWeapon;
}

void PlayerCharacter::addExp(std::string attribute, float expToAdd)
{
	if (attribute == "Melee")
	{
		int previousExp = static_cast<int>(this->melee);
		this->melee += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
	else if (attribute == "Ranged")
	{
		int previousExp = static_cast<int>(this->melee);
		this->ranged += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
	else if (attribute == "Woodcutting")
	{
		int previousExp = static_cast<int>(this->melee);
		this->woodcutting += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
	else if (attribute == "Mining")
	{
		int previousExp = static_cast<int>(this->melee);
		this->mining += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
	else if (attribute == "Hunting")
	{
		int previousExp = static_cast<int>(this->melee);
		this->hunting += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
	else if (attribute == "Engineering")
	{
		int previousExp = static_cast<int>(this->melee);
		this->engineering += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
	else if (attribute == "Construction")
	{
		int previousExp = static_cast<int>(this->melee);
		this->construction += expToAdd;
		int afterExp = static_cast<int>(this->melee);
		if (previousExp < afterExp)
		{
			this->addBaseExp();
		}
	}
}

void PlayerCharacter::addBaseExp()
{
	this->baseExp += 1;
	if (this->baseExp == 5)
	{
		this->increaseMaxHP(10);
		this->increaseBaseStamina(10);
		this->baseLevel += 1;
		this->baseExp = 0;
	}
}

void PlayerCharacter::increaseBaseStamina(const int stamina)
{
	this->stamina += stamina;
}

int PlayerCharacter::getBaseLevel() const
{
	return this->baseLevel;
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

int PlayerCharacter::getCookingLevel() const
{
	return static_cast<int>(this->cooking);
}

int PlayerCharacter::getConstructionLevel() const
{
	return static_cast<int>(this->construction);
}
