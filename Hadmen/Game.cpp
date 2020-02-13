#include "Game.h"

Game::Game() : GameState("Game")
{
	this->baseImage.loadFromFile("../Images/BaseImage.png");
	this->tileMap = new TileMap(this->baseImage);
}

Game::~Game()
{
	delete this->tileMap;
}

State Game::update()
{
	elapsedTimeSinceLastUpdate += clock.restart();

	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
	}

	State state = State::NO_CHANGE;
	return state;
}

void Game::render()
{
	window.clear();
	this->tileMap->renderTileMap(this->window);
	window.display();
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}
