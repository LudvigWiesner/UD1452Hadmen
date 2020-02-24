#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Reshandler.h"
#include "PlayerCharacter.h"
#include "UI.h"

class Game : public GameState
{
private:
	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate;
	sf::Time timePerFrame;

	sf::Image baseImage;
	sf::View* camera;

	TileMap* tileMap;
	ResHandler resourceHandler;
	sf::CircleShape circle;

	PlayerCharacter* PCOne;
	PlayerCharacter* PCTwo;
	sf::Vector2i mouseClickPosition;

	UI* userInterface;

public:
	Game(float windowWidth, float windowHeight);
	virtual ~Game();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};