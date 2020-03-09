#pragma once
#ifndef UI_H
#define UI_H
#include "SFML/Graphics.hpp"
#include "PlayerCharacter.h"
#include "Melee.h"
#include "Reshandler.h"


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

	sf::RectangleShape staminaBarOne;
	sf::RectangleShape staminaBarTwo;
	sf::Text staminaOne;
	sf::Text staminaTwo;

	Clickable* CharOneButton;
	Clickable* CharTwoButton;

	sf::RectangleShape enemyHP[10];
	Melee** meleeEnemies;
	int meleeCapacity;
	int nrOfMelees;

	void updateCharacterGUI();
	void updateUIPositions();
	void expand();
public:
	UI(sf::RenderWindow* window, sf::View* camera, ResHandler* resourceHandler);
	~UI();

	void addPCToUI(PlayerCharacter* PC);
	void addEnemyToUI(Melee* melee);
	void updateUI();
	void drawUI(sf::RenderWindow* window);

	void openCloseCharacterInventory();
	void openCloseCharacterSkillScreen();
	void updateSkillScreen();
	void updateInventory();

	void moveToCharOne();
	void moveToCharTwo();
	Clickable* getButtonOne();
	Clickable* getButtonTwo();
	bool buttonOneContainsMouse(const sf::Vector2f &mousePos);
	bool buttonTwoContainsMouse(const sf::Vector2f &mousePos);
	void unstuckCamera();


};
#endif // !UI_H
