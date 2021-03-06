#pragma once
#ifndef UI_H
#define UI_H
#include "SFML/Graphics.hpp"
#include "PlayerCharacter.h"
#include "Reshandler.h"
#include "ResourceTile.h"
#include "Furnace.h"
#include "WaterPurifier.h"
#include "StoneBrick.h"


class UI
{
private:
	sf::Font fontOne;
	sf::Font fontTwo;

	sf::Text characterGUI;
	Item** characterInventory;
	sf::Text** nrOfEachItemInventory;
	int inventoryCapacity;
	int nrOfItems;
	
	sf::RenderWindow* window;
	sf::View* camera;

	PlayerCharacter** characters;
	int characterCapacity;
	int nrOfCharacters;

	sf::RectangleShape inventoryBackground;
	sf::Texture inventoryBackgroundTexture;
	bool drawInventory;

	bool drawSkillScreen;
	sf::RectangleShape skillScreenBackground;
	sf::Texture skillScreenBackgroundTexture;
	sf::Text skillScreen;

	sf::RectangleShape rectShape;
	sf::RectangleShape rectShapeTwo;
	sf::RectangleShape hpOneBorder;
	sf::RectangleShape hpTwoBorder;
	sf::Text HpOne;
	sf::Text HpTwo;

	Clickable* CharOneButton;
	Clickable* CharTwoButton;

	sf::Text MenyOption;
	bool drawMeny;

	sf::Text* craftingMenyOptions;
	int nrOfCraftingOptions;
	bool displayCraftingMeny;
	sf::Text craftingInfoBox;
	bool displayCraftingMenyInfoBox;
	sf::RectangleShape craftingMenyBackground;
	sf::Texture craftingMenyBackgroundTexture;

	sf::RectangleShape staminaBarOne;
	sf::RectangleShape staminaBarTwo;
	sf::Text staminaOne;
	sf::Text staminaTwo;

	bool craftFurnace;
	bool craftWaterPurifier;
	bool craftStoneBrick;

	void updateCharacterGUI();
	void updateUIPositions();
	void expand();
public:
	UI(sf::RenderWindow* window, sf::View* camera, ResHandler* resourceHandler);
	~UI();

	void addPCToUI(PlayerCharacter* PC);
	void updateUI();
	void drawUI(sf::RenderWindow* window);

	void openCloseCharacterInventory();
	bool getIfInventoryOpen()const;
	sf::FloatRect getInventoryBackgroundBounds()const;
	void openCloseCharacterSkillScreen();
	bool getIfSkillScreenOpen()const;
	sf::FloatRect getSkillSreenBackgroundBounds()const;
	void updateSkillScreen();
	void updateInventory();

	void moveToCharOne();
	void moveToCharTwo();
	Clickable* getButtonOne();
	Clickable* getButtonTwo();
	void unstuckCamera();

	void displayMeny(ResourceTile* tileToDisplay, const sf::Vector2f &position);
	void openCloseMeny(bool trigger);
	bool getIfMenyDrawn()const;
	sf::Vector2f getMenyPosition()const;
	sf::FloatRect getMenyBounds()const;

	void openCloseCraftingMeny();
	bool getIfCraftingMenyOpen()const;
	sf::FloatRect getCraftingMenyBounds(const int index);
	void displayCraftingInfoBox(const int index);
	void closeCraftingMenyInfoBox();
	sf::FloatRect getCraftingMenyBackgroundBounds()const;

	void interactWithInventory(sf::Vector2f mouseClickPosition);

	void updateCraftFurance(int state);
	void updateCraftWaterPurifier(int state);
	void updateCraftStoneBrick(int state);

	bool stateOfCraft(int type);
};
#endif // !UI_H
