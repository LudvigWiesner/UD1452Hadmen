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

	this->castPtr = nullptr;
	this->selectedTile = nullptr;

	this->furnace = new Furnace(29, &this->resourceHandler);
	this->waterPlant = new WaterPurifier(34, &this->resourceHandler);
	for (int i = 0; i < 10; i++)
	{
		this->stonebrick[i] = new StoneBrick(23, &this->resourceHandler);
	}

	this->maxStoneBricks = 9;
	this->currentBricks = 0;

	//this->furnaceSound.setSoundFile("furanceSound");
	//this->furnaceSound.setVolume(100);

	this->Wei = new Melee(18, &this->resourceHandler, 4, 2, "Bad Guy", 1000, 1000);
	this->Wei2 = new Ranged(18, &this->resourceHandler, 4, 2, "Bag Guy2", 1100, 1000);
	this->Wei3 = new Boss(18, &this->resourceHandler, 4, 2, "Bag Guy3", 1200, 1000);

	this->PCOne->addItem(Item(29, &this->resourceHandler, "Furnace"));
	this->PCOne->addItem(Item(34, &this->resourceHandler, "Water Purifier"));
}

Game::~Game()
{
	delete this->tileMap;
	delete this->PCOne;
	delete this->PCTwo;
	delete this->camera;
	delete this->userInterface;
	delete this->Wei;
	delete this->Wei2;
	delete this->Wei3;
	delete this->furnace;
	delete this->waterPlant;
	for (int i = 0; i < 10; i++)
	{
		delete this->stonebrick[i];
	}
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
		//melee
		if (this->Wei->ifPlayerDetected(this->Wei->targetSelection(this->PCOne, this->PCTwo)))
		{

		}
		this->Wei->atkCounter(timePerFrame);
		this->Wei->targetChangeCD(timePerFrame);
		//ranged
		if (this->Wei2->ifPlayerDetected(this->Wei2->targetSelection(this->PCOne, this->PCTwo)))
		{

		}
		this->Wei2->atkCounter(timePerFrame);
		this->Wei2->targetChangeCD(timePerFrame);
		//boss
		if (this->Wei3->ifPlayerDetected(this->Wei3->targetSelection(this->PCOne, this->PCTwo)))
		{

		}
		this->Wei3->atkCounter(timePerFrame);
		this->Wei3->targetChangeCD(timePerFrame);
		if (this->Wei3->aoeFlagReturn() != true)
		{
			this->Wei3->aoeTimmer(timePerFrame);
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
	if (this->Wei3->aoeFlagReturn() == false)
	{
		Wei3->aoe(&this->window);
	}
	window.draw(*this->PCOne);
	window.draw(*this->PCTwo);
	window.draw(*this->Wei);
	window.draw(*this->Wei2);
	window.draw(*this->Wei3);
	if (furnace->hasBeenPlaced() == true)
	{
		window.draw(*this->furnace);
	}
	if (waterPlant->hasBeenPlaced() == true)
	{
		window.draw(*this->waterPlant);
	}
	for (int i = 0; i < 10; i++)
	{
		if (stonebrick[i]->hasBeenPlaced() == true)
		{
			window.draw(*this->stonebrick[i]);
		}
	}
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
				if (this->PCOne->click(mouseWorldCoordinates) || this->PCTwo->click(mouseWorldCoordinates) ||
					this->userInterface->getButtonOne()->click(mouseWorldCoordinates) || this->userInterface->getButtonTwo()->click(mouseWorldCoordinates) ||
					this->userInterface->getIfInventoryOpen() && this->userInterface->getInventoryBackgroundBounds().contains(mouseWorldCoordinates) ||
					this->userInterface->getIfSkillScreenOpen() && this->userInterface->getSkillSreenBackgroundBounds().contains(mouseWorldCoordinates) ||
					this->userInterface->getIfCraftingMenyOpen() && this->userInterface->getCraftingMenyBackgroundBounds().contains(mouseWorldCoordinates) ||
					this->userInterface->getIfMenyDrawn())
				{
					if (this->PCOne->click(mouseWorldCoordinates))
					{
						this->PCOne->setSelected(true);
						this->playerGoToCoordinates = sf::Vector2f(this->PCOne->getPosition());
						this->PCTwo->setSelected(false);
						this->userInterface->updateInventory();
						this->userInterface->updateSkillScreen();
						this->PCOne->reset();
					}
					else if (this->PCTwo->click(mouseWorldCoordinates))
					{
						this->PCTwo->setSelected(true);
						this->playerGoToCoordinates = sf::Vector2f(this->PCTwo->getPosition());
						this->PCOne->setSelected(false);
						this->userInterface->updateInventory();
						this->userInterface->updateSkillScreen();
						this->PCTwo->reset();
					}
					else if (this->userInterface->getButtonOne()->click(mouseWorldCoordinates))
					{
						this->userInterface->moveToCharOne();
					}
					else if (this->userInterface->getButtonTwo()->click(mouseWorldCoordinates))
					{
						this->userInterface->moveToCharTwo();
					}
					if (this->userInterface->getIfInventoryOpen() && this->userInterface->getInventoryBackgroundBounds().contains(mouseWorldCoordinates))
					{
						this->userInterface->interactWithInventory(mouseWorldCoordinates);
						if (this->userInterface->stateOfCraft(1) == true)
						{

							if (PCOne->isSelected() == true)
							{
								int counter = 0;
								for (int i = 0; i < 10; i++)
								{
									if (furnace->isSamePlace(*PCOne, *stonebrick[i], window, *furnace))
									{
										counter++;
									}
								}
								if (furnace->isSamePlace(*PCOne, *waterPlant, window, *furnace))
								{
									counter++;
								}
								if (counter == 0)
								{
									this->furnace->build(PCOne);
									this->PCOne->removeItem("Furnace");
									this->userInterface->updateInventory();
								}
							}
							if (PCTwo->isSelected() == true)
							{
								int counter = 0;
								for (int i = 0; i < 10; i++)
								{
									if (furnace->isSamePlace(*PCTwo, *stonebrick[i], window, *furnace))
									{
										counter++;
									}
								}
								if (furnace->isSamePlace(*PCTwo, *waterPlant, window, *furnace))
								{
									counter++;
								}
								if (counter == 0)
								{
									this->furnace->build(PCTwo);
									this->PCTwo->removeItem("Furnace");
									this->userInterface->updateInventory();
								}
							}
						}
						//water purifier
						if (this->userInterface->stateOfCraft(2) == true)
						{
							if (PCOne->isSelected() == true)
							{
								int counter = 0;
								for (int i = 0; i < 10; i++)
								{
									if (waterPlant->isSamePlace(*PCOne, *stonebrick[i], window, *waterPlant))
									{
										counter++;
									}
								}
								if (furnace->isSamePlace(*PCOne, *furnace, window, *waterPlant))
								{
									counter++;
								}
								if (counter == 0)
								{
									this->waterPlant->build(PCOne);
									//this->waterPlant->setPositions();
									this->PCOne->removeItem("Water Purifier");
									this->userInterface->updateInventory();
								}
							}
							if (PCTwo->isSelected() == true)
							{
								int counter = 0;
								for (int i = 0; i < 10; i++)
								{
									if (waterPlant->isSamePlace(*PCTwo, *stonebrick[i], window, *waterPlant))
									{
										counter++;
									}
								}
								if (waterPlant->isSamePlace(*PCTwo, *furnace, window, *waterPlant))
								{
									counter++;
								}
								if (counter == 0)
								{
									this->waterPlant->build(PCTwo);
									//this->waterPlant->setPositions();
									this->PCTwo->removeItem("Water Purifier");
									this->userInterface->updateInventory();
								}
							}
						}
						//Stone brick
						if (this->userInterface->stateOfCraft(3) == true && currentBricks <= maxStoneBricks)
						{
							if (PCOne->isSelected() == true)
							{
								int counter = 0;
								for (int i = 0; i < 10; i++)
								{
									if (stonebrick[currentBricks]->isSamePlace(*PCOne, *stonebrick[i], window, *stonebrick[currentBricks]))
									{
										counter++;
									}
								}
								counter--;
								if (stonebrick[currentBricks]->isSamePlace(*PCOne, *furnace, window, *stonebrick[currentBricks])
									|| stonebrick[currentBricks]->isSamePlace(*PCOne, *waterPlant, window, *stonebrick[currentBricks]))
								{
									counter++;
								}
								if (counter == 0)
								{
									this->stonebrick[currentBricks]->build(PCOne);
									currentBricks++;
									this->PCOne->removeItem("Stone Block");
									this->userInterface->updateInventory();
								}

							}
							if (PCTwo->isSelected() == true)
							{
								int counter = 0;
								for (int i = 0; i < 10; i++)
								{
									if (stonebrick[currentBricks]->isSamePlace(*PCTwo, *stonebrick[i], window, *stonebrick[currentBricks]))
									{
										counter++;
									}
								}
								counter--;
								if (stonebrick[currentBricks]->isSamePlace(*PCTwo, *furnace, window, *stonebrick[currentBricks])
									|| stonebrick[currentBricks]->isSamePlace(*PCTwo, *waterPlant, window, *stonebrick[currentBricks]))
								{
									counter++;
								}
								if (counter == 0)
								{
									this->stonebrick[currentBricks]->build(PCTwo);
									currentBricks++;
									this->PCTwo->removeItem("Stone Block");
									this->userInterface->updateInventory();
								}
							}
							this->userInterface->updateCraftStoneBrick(0);
						}
					}
					if (this->userInterface->getIfMenyDrawn() && this->userInterface->getMenyBounds().contains(mouseWorldCoordinates))
					{
						if (this->PCOne->isSelected())
						{
							if (castPtr->getName() == "Aluminium Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(0, &this->resourceHandler, "Aluminium Ore", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Coal Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(22, &this->resourceHandler, "Coal", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Iron Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(2, &this->resourceHandler, "Iron Ore", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Stone Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(5, &this->resourceHandler, "Stone Ore", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Tree")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(24, &this->resourceHandler, "Log", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Woodcutting", 0.2f);
								}
							}
							else if (castPtr->getName() == "Water")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(25, &this->resourceHandler, "Water", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
								}
							}
							else if (castPtr->getName() == "Battery")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCOne->addItem(Item(27, &this->resourceHandler, "Battery", 1));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
								}
							}
							else if (castPtr->getName() == "Poisoned Water")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float wx = this->waterPlant->getPosition().x;
								float wy = this->waterPlant->getPosition().y;
								float distance = sqrt((px - wx) * (px - wx) + (py - wy) * (py - wy));
								if (distance < 150)
								{
									castPtr->switchTexture(&this->resourceHandler);
									castPtr->setName("Water");
								}
							}
						}
						else if (this->PCTwo->isSelected())
						{
							if (castPtr->getName() == "Aluminium Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCTwo->addItem(Item(0, &this->resourceHandler, "Aluminium Ore", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Coal Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCTwo->addItem(Item(22, &this->resourceHandler, "Coal", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Iron Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCTwo->addItem(Item(2, &this->resourceHandler, "Iron Ore", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Stone Deposit")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCTwo->addItem(Item(5, &this->resourceHandler, "Stone Ore", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Mining", 0.2f);
								}
							}
							else if (castPtr->getName() == "Tree")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCTwo->addItem(Item(24, &this->resourceHandler, "Log", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
									this->PCOne->addExp("Woodcutting", 0.2f);
								}
							}
							else if (castPtr->getName() == "Water")
							{
								float px = this->PCOne->getPosition().x;
								float py = this->PCOne->getPosition().y;
								float tx = castPtr->getPosition().x;
								float ty = castPtr->getPosition().y;
								float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
								if (distance < 150)
								{
									this->PCTwo->addItem(Item(25, &this->resourceHandler, "Water", this->castPtr->getResource()));
									this->userInterface->updateInventory();
									this->userInterface->openCloseMeny(false);
									this->castPtr->switchTexture(&this->resourceHandler);
								}
							}
							else if (castPtr->getName() == "Battery")
							{
							float px = this->PCOne->getPosition().x;
							float py = this->PCOne->getPosition().y;
							float tx = castPtr->getPosition().x;
							float ty = castPtr->getPosition().y;
							float distance = sqrt((px - tx) * (px - tx) + (py - ty) * (py - ty));
							if (distance < 150)
							{
								this->PCTwo->addItem(Item(27, &this->resourceHandler, "Battery", 1));
								this->userInterface->updateInventory();
								this->userInterface->openCloseMeny(false);
								this->castPtr->switchTexture(&this->resourceHandler);
							}
							}
							else if (castPtr->getName() == "Poisoned Water")
							{
								float wx = this->waterPlant->getPosition().x;
								float wy = this->waterPlant->getPosition().y;
								float px = this->PCTwo->getPosition().x;
								float py = this->PCTwo->getPosition().y;
								float distance = sqrt((px - wx) * (px - wx) + (py - wy) * (py - wy));
								if (distance < 150)
								{
									castPtr->switchTexture(&this->resourceHandler);
									castPtr->setName("Water");
								}
							}
						}
					}
					else
					{
						this->userInterface->openCloseMeny(false);
					}
					if (this->userInterface->getIfCraftingMenyOpen() && this->userInterface->getCraftingMenyBackgroundBounds().contains(mouseWorldCoordinates))
					{
						if (this->userInterface->getCraftingMenyBounds(1).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Log") >= 2 && this->PCOne->getNrOfAnItem("Iron Bar") >= 1)
								{
									this->PCOne->removeNrFromAnItem("Log", 2);
									this->PCOne->addItem(Item(30, &this->resourceHandler, "Pickaxe"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Log") >= 2 && this->PCTwo->getNrOfAnItem("Iron Bar") >= 1)
								{
									this->PCTwo->removeNrFromAnItem("Log", 2);
									this->PCTwo->addItem(Item(30, &this->resourceHandler, "Pickaxe"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(2).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Log") >= 2 && this->PCOne->getNrOfAnItem("Iron Bar") >= 1)
								{
									this->PCOne->removeNrFromAnItem("Log", 2);
									this->PCOne->addItem(Item(28, &this->resourceHandler, "Axe"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Log") >= 2 && this->PCTwo->getNrOfAnItem("Iron Bar") >= 1)
								{
									this->PCTwo->removeNrFromAnItem("Log", 2);
									this->PCTwo->addItem(Item(28, &this->resourceHandler, "Axe"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(3).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Log") >= 2)
								{
									this->PCOne->removeNrFromAnItem("Log", 2);
									this->PCOne->addItem(Item(33, &this->resourceHandler, "Bucket"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Log") >= 2)
								{
									this->PCTwo->removeNrFromAnItem("Log", 2);
									this->PCTwo->addItem(Item(33, &this->resourceHandler, "Bucket"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(4).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Iron Ore") >= 3)
								{
									this->PCOne->removeNrFromAnItem("Iron Ore", 3);
									this->PCOne->addItem(Item(20, &this->resourceHandler, "Iron Bar"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Iron Ore") >= 3)
								{
									this->PCTwo->removeNrFromAnItem("Iron Ore", 3);
									this->PCTwo->addItem(Item(20, &this->resourceHandler, "Iron Bar"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(5).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Aluminium Ore") >= 3)
								{
									this->PCOne->removeNrFromAnItem("Aluminium Ore", 3);
									this->PCOne->addItem(Item(21, &this->resourceHandler, "Aluminium Bar"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Aluminium Ore") >= 3)
								{
									this->PCTwo->removeNrFromAnItem("Aluminium Ore", 3);
									this->PCTwo->addItem(Item(21, &this->resourceHandler, "Aluminium Bar"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(6).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Stone Ore") >= 3)
								{
									this->PCOne->removeNrFromAnItem("Stone Ore", 3);
									this->PCOne->addItem(Item(23, &this->resourceHandler, "Stone Block"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Stone Ore") >= 3)
								{
									this->PCTwo->removeNrFromAnItem("Stone Ore", 3);
									this->PCTwo->addItem(Item(23, &this->resourceHandler, "Stone Block"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(7).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Stone Block") >= 3)
								{
									this->PCOne->removeNrFromAnItem("Stone Block", 3);
									this->PCOne->addItem(Item(29, &this->resourceHandler, "Furnace"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Stone Block") >= 3)
								{
									this->PCTwo->removeNrFromAnItem("Stone Block", 3);
									this->PCTwo->addItem(Item(29, &this->resourceHandler, "Furnace"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(8).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Iron Bar") >= 1 && this->PCOne->getNrOfAnItem("Aluminium Bar") >= 3 && this->PCOne->getNrOfAnItem("Battery") >= 1)
								{
									this->PCOne->removeNrFromAnItem("Iron Bar", 1);
									this->PCOne->removeNrFromAnItem("Aluminium Bar", 3);
									this->PCOne->removeNrFromAnItem("Battery", 1);
									this->PCOne->addItem(Item(34, &this->resourceHandler, "Water Purifier"));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Iron Bar") >= 1 && this->PCTwo->getNrOfAnItem("Aluminium Bar") >= 3 && this->PCTwo->getNrOfAnItem("Battery") >= 1)
								{
									this->PCTwo->removeNrFromAnItem("Iron Bar", 1);
									this->PCTwo->removeNrFromAnItem("Aluminium Bar", 3);
									this->PCTwo->removeNrFromAnItem("Battery", 1);
									this->PCTwo->addItem(Item(34, &this->resourceHandler, "Water Purifier"));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(9).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Iron Bar") >= 2 && this->PCOne->getNrOfAnItem("Aluminium Bar") >= 3)
								{
									this->PCOne->removeNrFromAnItem("Iron Bar", 2);
									this->PCOne->removeNrFromAnItem("Aluminium Bar", 3);
									this->PCOne->addItem(Item(32, &this->resourceHandler, "Nail Gun", true, 1, 20));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Iron Bar") >= 2 && this->PCTwo->getNrOfAnItem("Aluminium Bar") >= 3)
								{
									this->PCTwo->removeNrFromAnItem("Iron Bar", 2);
									this->PCTwo->removeNrFromAnItem("Aluminium Bar", 3);
									this->PCTwo->addItem(Item(32, &this->resourceHandler, "Nail Gun", true, 1, 20));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(10).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Iron Bar") >= 3 && this->PCOne->getNrOfAnItem("Log") >= 1)
								{
									this->PCOne->removeNrFromAnItem("Iron Bar", 3);
									this->PCOne->removeNrFromAnItem("Log", 1);
									this->PCOne->addItem(Item(31, &this->resourceHandler, "Machete", true, 1, 10));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Iron Bar") >= 3 && this->PCTwo->getNrOfAnItem("Log") >= 1)
								{
									this->PCTwo->removeNrFromAnItem("Iron Bar", 3);
									this->PCTwo->removeNrFromAnItem("Log", 1);
									this->PCTwo->addItem(Item(31, &this->resourceHandler, "Machete", true, 1, 10));
									this->userInterface->updateInventory();
								}
							}
						}
						else if (this->userInterface->getCraftingMenyBounds(11).contains(this->mouseWorldCoordinates))
						{
							if (this->PCOne->isSelected())
							{
								if (this->PCOne->getNrOfAnItem("Machete") >= 1)
								{
									this->PCOne->removeNrFromAnItem("Machete", 1);
									this->PCOne->addItem(Item(31, &this->resourceHandler, "Electric Machete", true, 1, 20));
									this->userInterface->updateInventory();
								}
							}
							else if (this->PCTwo->isSelected())
							{
								if (this->PCTwo->getNrOfAnItem("Machete") >= 1)
								{
									this->PCTwo->removeNrFromAnItem("Machete", 1);
									this->PCTwo->addItem(Item(31, &this->resourceHandler, "Electric Machete", true, 1, 20));
									this->userInterface->updateInventory();
								}
							}
						}
					}
				}
				else
				{
					this->playerGoToCoordinates = mouseWorldCoordinates;
				}
			}
			if (event.key.code == sf::Mouse::Button::Right)
			{
				int xPos = static_cast<int>(this->mouseWorldCoordinates.x);
				int yPos = static_cast<int>(this->mouseWorldCoordinates.y);

				xPos = xPos / 50;
				yPos = yPos / 50;

				this->selectedTile = this->tileMap->getTile(xPos, yPos);
				this->castPtr = dynamic_cast<ResourceTile*>(selectedTile);

				if (castPtr != nullptr && this->castPtr->getIfHasResource())
				{
					this->userInterface->displayMeny(castPtr, mouseWorldCoordinates);
					this->userInterface->openCloseMeny(true);
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
			else if (event.key.code == sf::Keyboard::B)
			{
				this->userInterface->openCloseCraftingMeny();
			}
			break;
		case sf::Event::MouseMoved:
			if (this->userInterface->getIfCraftingMenyOpen())
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
				if (this->userInterface->getCraftingMenyBounds(1).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(1);
				}
				if (this->userInterface->getCraftingMenyBounds(2).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(2);
				}
				if (this->userInterface->getCraftingMenyBounds(3).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(3);
				}
				if (this->userInterface->getCraftingMenyBounds(4).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(4);
				}
				if (this->userInterface->getCraftingMenyBounds(5).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(5);
				}
				if (this->userInterface->getCraftingMenyBounds(6).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(6);
				}
				if (this->userInterface->getCraftingMenyBounds(7).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(7);
				}
				if (this->userInterface->getCraftingMenyBounds(8).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(8);
				}
				if (this->userInterface->getCraftingMenyBounds(9).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(9);
				}
				if (this->userInterface->getCraftingMenyBounds(10).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(10);
				}
				if (this->userInterface->getCraftingMenyBounds(11).contains(mousePosF))
				{
					this->userInterface->displayCraftingInfoBox(11);
				}
			}
		}
	}
}

