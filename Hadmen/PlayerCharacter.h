#pragma once
#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H
#include "Entity.h"
#include "List.h"
#include "Weapon.h"
#include "Item.h"

//TODO: Add base level increase stamina hp
class PlayerCharacter : public Entity
{
private:
	bool selected;
	List<Item*>* inventory;
	Item* equippedWeapon;

	int baseLevel;
	int baseExp;
	int stamina;

	float melee;
	float ranged;
	float woodcutting;
	float mining;
	float hunting;
	float engineering;
	float cooking;
	float construction;

	void addBaseExp();
	void increaseBaseStamina(const int stamina);
public:
	PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed = 3.0F);
	~PlayerCharacter();

	void setSelected(const bool set);
	bool isSelected()const;
	sf::Vector2f getPlayerPosition()const;

	void addItem(const Item itemToAdd);
	void removeItem(Item* itemToRemove);
	void removeItem(const std::string itemName);
	int getNrOfAnItem(Item* itemToCount);
	int getNrOfAnItem(const int index);
	int getNrOfAnItem(const std::string itemName);
	int getNrOfItems()const;
	void getAllItems(Item* arr[]);

	void addNrToAnItem(Item* itemToAddTo, const int nr);
	void removeNrFromAnItem(Item* itemToRemoveFrom, const int nr);
	void removeNrFromAnItem(const std::string itemName, const int nr);

	int getEquippedWeaponDamage()const;
	void equipWeapon(Item* itemToEquip);
	Item* getEquippedWeapon()const;
	
	void addExp(std::string attribute, float expToAdd);
	int getBaseLevel()const;
	int getMeleeLevel()const;
	int getRangedLevel()const;
	int getWoodcuttingLevel()const;
	int getMiningLevel()const;
	int getHuntingLevel()const;
	int getEngineeringLevel()const;
	int getCookingLevel()const;
	int getConstructionLevel()const;
};
#endif // !CHARACTER_H
