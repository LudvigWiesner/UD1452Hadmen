#include "Game.h"
#include <iostream>

Game::Game(float windowWidth, float windowHeight) : GameState("Game", windowWidth, windowHeight)
{
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	this->baseImage.loadFromFile("../Images/BaseImage.png");
	this->tileMap = new TileMap(this->baseImage, &this->resourceHandler);
	camera = new sf::View(sf::Vector2f(windowWidth/2, windowHeight/2),sf::Vector2f(windowWidth,windowHeight));

	this->PCOne = new PlayerCharacter(15, &this->resourceHandler, 4, 4);
	this->PCTwo = new PlayerCharacter(17, &this->resourceHandler, 4, 4);
	this->PCTwo->setCoordinates(500, 500);
	
	this->userInterface = new UI(&window, camera);
	this->userInterface->addPCToUI(PCOne);
	this->userInterface->addPCToUI(PCTwo);

	Item tempWeapon(16, &this->resourceHandler, "Wie's doom", 5);
	this->PCOne->addItem(tempWeapon);
	this->PCOne->equipWeapon(tempWeapon);
	this->PCTwo->equipWeapon(tempWeapon);
}

Game::~Game()
{
	delete this->tileMap;
	delete this->PCOne;
	delete this->PCTwo;
	delete this->camera;
	delete this->userInterface;
}

State Game::update()
{
	State state = State::NO_CHANGE;
	elapsedTimeSinceLastUpdate += clock.restart();
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;

		if ((camera->getCenter().x >= ((windowWidth / 2) )) && (camera->getCenter().y >= ((windowHeight / 2) )))
		{
			if ((sf::Mouse::getPosition().x > windowWidth - windowWidth / 5) && (camera->getCenter().x <= 108*50 - (windowWidth/2)))
			{
				camera->move(5,0);
			}
			
			else if ((camera->getCenter().x > windowWidth / 2 + 5) && sf::Mouse::getPosition().x <windowWidth/5 ) 
			{
				camera->move(-5, 0);
			}
			if ((sf::Mouse::getPosition().y > windowHeight - windowHeight / 5) && (camera->getCenter().y <= 108 * 50 - (windowHeight / 2)))
			{
				camera->move(0, 5);
			}
			else if ((camera->getCenter().y > windowHeight/2 +5) && (sf::Mouse::getPosition().y < windowHeight/5 ) )
			{
				camera->move(0, -5);
			}
		}
		userInterface->updateUI();
		if (this->PCOne->isSelected())
		{
			this->PCOne->moveEntityTo(this->mouseClickPosition);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				this->PCOne->makeAttack(*PCTwo, this->PCOne->getEquippedWeaponDamage());
			}
		}
		if (this->PCTwo->isSelected())
		{
			this->PCTwo->moveEntityTo(this->mouseClickPosition);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				this->PCTwo->makeAttack(*PCOne, this->PCTwo->getEquippedWeaponDamage());
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			state = State::EXIT;
		}
		
	}
	return state;
}

void Game::render()
{
	window.clear();
	this->tileMap->renderTileMap(this->window);
	window.setView(*camera);
	window.draw(*this->PCOne);
	window.draw(*this->PCTwo);
	this->userInterface->drawUI(&this->window);
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
		if (this->PCOne->click(window, event))
		{
			this->PCOne->setSelected(true);
			this->PCTwo->setSelected(false);
			this->PCOne->reset();
		}
		if (this->PCTwo->click(window, event))
		{
			this->PCTwo->setSelected(true);
			this->PCOne->setSelected(false);
			this->PCTwo->reset();
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			this->mouseClickPosition = sf::Mouse::getPosition();
		}
	}
}

