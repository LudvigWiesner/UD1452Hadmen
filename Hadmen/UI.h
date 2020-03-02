#pragma once
#ifndef UI_H
#define UI_H
#include "SFML/Graphics.hpp"
#include "PlayerCharacter.h"
#include "Reshandler.h"
#include <vector>

class UI
{
private:
	sf::Font fontOne;

	sf::Text characterGUI;
	Item* characterInventory;
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

	sf::RectangleShape rectShape;
	sf::RectangleShape rectShapeTwo;

	sf::RectangleShape hpOneBorder;
	sf::RectangleShape hpTwoBorder;

	sf::RectangleShape CharOneButton;
	sf::RectangleShape CharTwoButton;

	sf::Text HpOne;
	sf::Text HpTwo;

	void updateCharacterGUI();
	void updateUIPositions();
	
	void expand();
public:
	UI(sf::RenderWindow* window, sf::View* camera, ResHandler* resourceHandler);
	~UI();

	void addPCToUI(PlayerCharacter* PC);
	void updateUI();

	void moveToProfile();
	void unstuckCamera();

	void drawUI(sf::RenderWindow* window);
	void openCloseCharacterInventory();


};
#endif // !UI_H
