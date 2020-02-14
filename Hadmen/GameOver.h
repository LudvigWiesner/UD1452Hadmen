#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class GameOver : public GameState
{
private:
	sf::Text labelText; 
	sf::Text text; 
	sf::Font font;
	std::string name; 
	bool done;
public:
	GameOver(float windowWidth, float windowHeight);
	virtual ~GameOver();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};