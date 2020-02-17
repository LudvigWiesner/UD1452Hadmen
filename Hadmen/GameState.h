#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include <string>

class GameState
{
protected:
	sf::RenderWindow window;
	float windowWidth;
	float windowHeight;
public:
	GameState(std::string title, float windowWidth, float windowHeight);
	virtual ~GameState();
	virtual State update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
};
