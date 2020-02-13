#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"

class Game : public GameState
{
public:
	static const int HEIGHT = 600;
	static const int WIDTH = 900;
private:
	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate;
	sf::Time timePerFrame;

	sf::Image baseImage;
	TileMap* tileMap;
public:
	Game();
	virtual ~Game();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};