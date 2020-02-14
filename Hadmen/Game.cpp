#include "Game.h"

Game::Game(float windowWidth, float windowHeight) : GameState("Game", windowWidth, windowHeight)
{
	//this->baseImage.loadFromFile("../Images/BaseImage.png");
	//this->tileMap = new TileMap(this->baseImage);
	circle.setRadius(50.0f);
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(10.f, 250.f);
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);
}

Game::~Game()
{
	//delete this->tileMap;
}

State Game::update()
{
	elapsedTimeSinceLastUpdate += clock.restart();

	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
		circle.move(4.f, 0);
	}

	State state = State::NO_CHANGE;
	if (circle.getGlobalBounds().left + circle.getGlobalBounds().width > 600.0f) //Spelet tar slut
	{
		state = State::GAME_OVER;
	}
	return state;
}

void Game::render()
{
	window.clear();
	//this->tileMap->renderTileMap(this->window);
	window.draw(circle);
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
