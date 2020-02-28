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
	void openCloseCharacterSkillScreen();
	void updateSkillScreen();
	void updateInventory();
};
#endif // !UI_H
