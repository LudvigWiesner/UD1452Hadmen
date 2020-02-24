#pragma once
#ifndef UI_H
#define UI_H
#include "SFML/Graphics.hpp"
#include "PlayerCharacter.h"

class UI
{
private:
	sf::Font fontOne;

	sf::Text characterGUI;

	sf::RenderWindow* window;
	sf::View* camera;

	PlayerCharacter** characters;
	int characterCapacity;
	int nrOfCharacters;

	void updateCharacterGUI();

	
public:
	UI(sf::RenderWindow* window, sf::View* camera);
	~UI();

	void addPCToUI(PlayerCharacter* PC);
	void updateUI();

	void drawUI(sf::RenderWindow* window);
};
#endif // !UI_H
