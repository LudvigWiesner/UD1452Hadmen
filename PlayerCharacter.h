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
	int maxStamina;

	float melee;
	float ranged;
	float woodcutting;
	float mining;
	float hunting;
	float engineering;
	float cooking;
	float construction;

	void addExp(std::string attribute, float expToAdd);
	void addBaseExp();
	void increaseBaseStamina(const int stamina);
public:
	PlayerCharacter(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, float speed = 3.0F);
	~PlayerCharacter();

	void setSelected(const bool set);
	bool isSelected()const;
	sf::Vector2f getPlayerPosition()const;

	int getStamina() const;
	int getMaxStamina() const;

	void addItem(const Item itemToAdd);
	void removeItem(Item* itemToRemove);
	int getNrOfAnItem(Item* itemToCount);
	int getNrOfAnItem(const int index);
	int getNrOfItems()const;
	void getAllItems(Item* arr[]);

	void addNrToAnItem(Item* itemToAddTo, const int nr);
	void removeNrFromAnItem(Item* itemToRemoveFrom, const int nr);

	int getEquippedWeaponDamage()const;
	void equipWeapon(const Item itemToEquip);
	
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
