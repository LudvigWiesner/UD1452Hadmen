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
	
	this->userInterface = new UI(&window, camera, &this->resourceHandler);
	this->userInterface->addPCToUI(PCOne);
	this->userInterface->addPCToUI(PCTwo);

	Item tempWeapon(16, &this->resourceHandler, "Wie's doom", 5);
	this->PCOne->addItem(tempWeapon);
	this->PCTwo->addItem(tempWeapon);
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
			if ((sf::Mouse::getPosition().x > windowWidth - windowWidth / 25) && (camera->getCenter().x <= 108*50 - (windowWidth/2)))
			{
				camera->move(5,0);
			}
			
			else if ((camera->getCenter().x > windowWidth / 2 + 5) && sf::Mouse::getPosition().x <windowWidth/5 ) 
			{
				camera->move(-5, 0);
			}
			if ((sf::Mouse::getPosition().y > windowHeight - windowHeight / 25) && (camera->getCenter().y <= 108 * 50 - (windowHeight / 2)))
			{
				camera->move(0, 5);
			}
			else if ((camera->getCenter().y > windowHeight/ 2 + 5) && (sf::Mouse::getPosition().y < windowHeight/ 5 ) )
			{
				camera->move(0, -5);
			}
		}
		userInterface->updateUI();
		if (this->PCOne->isSelected())
		{
			this->PCOne->moveEntityTo(this->mouseWorldCoordinates);
		}
		if (this->PCTwo->isSelected())
		{
			this->PCTwo->moveEntityTo(this->mouseWorldCoordinates);
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
		switch (event.type)
		{
		case sf::Event::Closed:
				window.close();
				break;

		case sf::Event::MouseButtonReleased:
			this->mouseClickWindowPosition = sf::Mouse::getPosition(window);
			this->mouseWorldCoordinates = window.mapPixelToCoords(mouseClickWindowPosition);
			if (event.key.code == sf::Mouse::Button::Left)
			{
				if (this->PCOne->click(mouseWorldCoordinates))
				{
					this->PCOne->setSelected(true);
					this->PCTwo->setSelected(false);
					this->PCOne->reset();
				}
				if (this->PCTwo->click(mouseWorldCoordinates))
				{
					this->PCTwo->setSelected(true);
					this->PCOne->setSelected(false);
					this->PCTwo->reset();
				}
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::I)
			{
				this->userInterface->openCloseCharacterInventory();
			}
			break;
		}
	}
}

