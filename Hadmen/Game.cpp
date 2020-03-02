#include "Game.h"
#include <iostream>

Game::Game(float windowWidth, float windowHeight) : GameState("Game", windowWidth, windowHeight)
{
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	this->baseImage.loadFromFile("../Images/BaseImage.png");
	this->tileMap = new TileMap(this->baseImage, &this->resourceHandler);
	camera = new sf::View(sf::Vector2f(windowWidth/2, windowHeight/2),sf::Vector2f(windowWidth,windowHeight));

	this->itemHandler = new ItemHandler(&this->resourceHandler);

	this->PCOne = new PlayerCharacter(15, &this->resourceHandler, 4, 4);
	this->PCTwo = new PlayerCharacter(17, &this->resourceHandler, 4, 4);
	this->PCTwo->setCoordinates(500, 500);
	
	this->userInterface = new UI(&window, camera, &this->resourceHandler);
	this->userInterface->addPCToUI(PCOne);
	this->userInterface->addPCToUI(PCTwo);

	this->PCOne->addItem(this->itemHandler->getItem(1));
	this->PCOne->addItem(this->itemHandler->getItem(0));
	this->PCOne->addItem(this->itemHandler->getItem(2));
	this->PCOne->addItem(this->itemHandler->getItem(3));
	this->PCOne->addItem(this->itemHandler->getItem(4));
	this->PCOne->addItem(this->itemHandler->getItem(5));
	this->PCOne->addItem(this->itemHandler->getItem(7));
	this->PCOne->addItem(this->itemHandler->getItem(5));
	this->PCOne->addItem(this->itemHandler->getItem(5));

	this->PCOne->addNrToAnItem(&this->itemHandler->getItem(1), 2);
	this->PCOne->addNrToAnItem(&this->itemHandler->getItem(3), 6);
	this->PCOne->addNrToAnItem(&this->itemHandler->getItem(4), 12);

	this->PCOne->equipWeapon(this->itemHandler->getItem(7));
	this->PCTwo->equipWeapon(this->itemHandler->getItem(7));

	this->Wei = new Melee(18, &this->resourceHandler, 4, 2, "Bad Guy", 1000, 1000);
}

Game::~Game()
{
	delete this->tileMap;
	delete this->PCOne;
	delete this->PCTwo;
	delete this->camera;
	delete this->userInterface;
	delete this->itemHandler;
	delete this->Wei;
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
			this->PCOne->moveEntityTo(this->playerGoToCoordinates);
		}
		if (this->PCTwo->isSelected())
		{
			this->PCTwo->moveEntityTo(this->playerGoToCoordinates);
		}
		if (this->Wei->ifPlayerDetected(this->Wei->targetSelection(this->PCOne, this->PCTwo)))
		{

		}
		this->Wei->atkCounter(timePerFrame);
		this->Wei->targetChangeCD(timePerFrame);
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
	window.draw(*this->Wei);
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
				this->playerGoToCoordinates = mouseWorldCoordinates;
				if (this->PCOne->click(mouseWorldCoordinates))
				{
					this->PCOne->setSelected(true);
					this->PCTwo->setSelected(false);
					this->userInterface->updateInventory();
					this->userInterface->updateSkillScreen();
					this->PCOne->reset();
				}
				if (this->PCTwo->click(mouseWorldCoordinates))
				{
					this->PCTwo->setSelected(true);
					this->PCOne->setSelected(false);
					this->userInterface->updateInventory();
					this->userInterface->updateSkillScreen();
					this->PCTwo->reset();
				}
				if (this->userInterface->getButtonOne()->click(mouseWorldCoordinates))
				{
					this->userInterface->moveToCharOne();
				}
				if (this->userInterface->getButtonTwo()->click(mouseWorldCoordinates))
				{
					this->userInterface->moveToCharTwo();
				}
			}
			if (event.key.code == sf::Mouse::Button::Right)
			{
				if (this->PCOne->isSelected())
				{
					int xPos = static_cast<int>(this->mouseWorldCoordinates.x);
					int yPos = static_cast<int>(this->mouseWorldCoordinates.y);
					TileEntity* selectedTile;
					ResourceTile* castPtr;
					if (xPos % 50 == 0)
					{
						xPos = xPos / 50;
					}
					else
					{
						xPos = xPos / 50 + 1;
					}
					if (yPos % 50 == 0)
					{
						yPos = yPos / 50;
					}
					else
					{
						yPos = yPos / 50 + 1;
					}
					selectedTile = this->tileMap->getTile(xPos, yPos);
					
					castPtr = dynamic_cast<ResourceTile*>(selectedTile);
					if (castPtr != nullptr)
					{

					}
				}
				else if (this->PCTwo->isSelected())
				{

				}
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::I)
			{
				this->userInterface->openCloseCharacterInventory();
			}
			else if (event.key.code == sf::Keyboard::C)
			{
				this->userInterface->openCloseCharacterSkillScreen();
			}
			else if (event.key.code == sf::Keyboard::H)
			{
				this->PCOne->removeNrFromAnItem(&this->itemHandler->getItem(4), 4);
				this->userInterface->updateUI();
			}
			else if (event.key.code == sf::Keyboard::J)
			{
				this->PCOne->removeItem(&this->itemHandler->getItem(1));
				this->userInterface->updateUI();
			}
			break;
		}
	}
}

