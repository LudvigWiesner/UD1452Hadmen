#include "UI.h"
#include <iostream>

void UI::updateCharacterGUI()
{
	this->rectShape.setSize(sf::Vector2f(static_cast<float>(this->characters[0]->getCurrentHP()) * 2.0f, 40.0f));
	this->rectShapeTwo.setSize(sf::Vector2f(static_cast<float>(this->characters[1]->getCurrentHP()) * 2.0f, 40.0f));
	this->HpOne.setString(std::to_string(characters[0]->getMaxHP()) + "/" + std::to_string(this->characters[0]->getCurrentHP()));
	this->HpTwo.setString(std::to_string(characters[1]->getMaxHP()) + "/" + std::to_string(this->characters[1]->getCurrentHP()));
}

void UI::updateUIPositions()
{
	int xOffSet = 0;
	int yOffSet = 0;
	int yCounter = 0;

	this->characterGUI.setPosition(5 + camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2);
	this->inventoryBackground.setPosition(camera->getCenter().x - this->inventoryBackground.getGlobalBounds().width + window->getSize().x / 2, camera->getCenter().y + 20 - window->getSize().y / 2);
	for (int i = 0; i < this->nrOfItems; i++)
	{
		this->characterInventory[i]->setCoordinates(camera->getCenter().x + window->getSize().x / 2 - 300 + xOffSet, camera->getCenter().y - this->window->getSize().y / 2 + yOffSet + 40);
		this->nrOfEachItemInventory[i]->setPosition(camera->getCenter().x + window->getSize().x / 2 - 300 + xOffSet, camera->getCenter().y - this->window->getSize().y / 2 + yOffSet + 40);
		
		xOffSet += 60;
		xOffSet = xOffSet % 300;
		if (yCounter == 4)
		{
			yOffSet += 60;
			yCounter = 0;
		}
		else
		{
			yCounter++;
		}
	}
	this->inventoryBackground.setSize(sf::Vector2f(300.0f, 80.0f + static_cast<float>(yOffSet)));
	this->skillScreenBackground.setPosition(camera->getCenter().x + this->window->getSize().x / 2 - this->skillScreenBackground.getGlobalBounds().width - this->inventoryBackground.getGlobalBounds().width, camera->getCenter().y - this->window->getSize().y / 2 + 20);
	this->skillScreen.setPosition(camera->getCenter().x + window->getSize().x / 2 - this->skillScreen.getGlobalBounds().width - this->inventoryBackground.getGlobalBounds().width - 20, camera->getCenter().y - this->window->getSize().y / 2 + 20);

	this->rectShape.setPosition(40 + camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2 + 40);
	this->rectShapeTwo.setPosition(rectShape.getPosition().x, rectShape.getPosition().y + 60);

	this->hpOneBorder.setPosition(rectShape.getPosition().x - 10, rectShape.getPosition().y - 5);
	this->hpTwoBorder.setPosition(rectShapeTwo.getPosition().x - 10, rectShapeTwo.getPosition().y - 5);

	this->CharOneButton->setCoordinates(rectShape.getPosition().x + 225, rectShape.getPosition().y);
	this->CharTwoButton->setCoordinates(CharOneButton->getPosition().x, rectShapeTwo.getPosition().y);
	
	this->HpOne.setPosition(rectShape.getPosition().x + 30, rectShape.getPosition().y - 8);
	this->HpTwo.setPosition(rectShapeTwo.getPosition().x + 30, rectShapeTwo.getPosition().y - 8);

	yOffSet = 0;
	for (int i = 0; i < this->nrOfCraftingOptions; i++)
	{
		this->craftingMenyOptions[i].setPosition(this->skillScreen.getPosition().x - this->craftingMenyOptions[11].getGlobalBounds().width, this->camera->getCenter().y - this->window->getSize().y / 2 + 20 + yOffSet);
		yOffSet += 60;
	}
	this->craftingMenyBackground.setPosition(this->craftingMenyOptions[0].getPosition());

	this->staminaBarOne.setPosition(rectShape.getPosition().x, rectShape.getPosition().y + 40);
	this->staminaBarTwo.setPosition(rectShapeTwo.getPosition().x, rectShapeTwo.getPosition().y + 40);

	this->staminaOne.setPosition(staminaBarOne.getPosition().x + 35, staminaBarOne.getPosition().y - 8);
	this->staminaTwo.setPosition(staminaBarTwo.getPosition().x + 35, staminaBarTwo.getPosition().y - 8);
}

void UI::expand()
{
	Item** temp;
	sf::Text** temp1;
	this->inventoryCapacity = this->inventoryCapacity * 2;

	temp = new Item* [this->inventoryCapacity];
	temp1 = new sf::Text * [this->inventoryCapacity];

	for (int i = 0; i < this->nrOfItems;i++)
	{
		temp[i] = this->characterInventory[i];
		temp1[i] = this->nrOfEachItemInventory[i];
	}
	delete[]this->nrOfEachItemInventory;
	delete[]this->characterInventory;

	this->characterInventory = temp;
	this->nrOfEachItemInventory = temp1;
}

UI::UI(sf::RenderWindow* window, sf::View* camera, ResHandler* resourceHandler)
{
	this->window = window;
	this->camera = camera;
	this->fontOne.loadFromFile("../images/TrenchThin-aZ1J.ttf");
	this->fontTwo.loadFromFile("../images/arial.ttf");
	this->characterGUI.setFont(this->fontOne);
	this->characterGUI.setCharacterSize(60);
	this->characterGUI.setFillColor(sf::Color::Black);
	this->characterGUI.setPosition(camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2);

	this->nrOfCharacters = 0;
	this->characterCapacity = 2;
	this->characters = new PlayerCharacter * [characterCapacity];

	this->drawInventory = false;
	this->inventoryBackgroundTexture = resourceHandler->getTexture(19);
	this->inventoryBackground.setTexture(&this->inventoryBackgroundTexture);
	
	this->inventoryCapacity = 50;
	this->nrOfItems = 0;
	this->characterInventory = new Item * [inventoryCapacity] {nullptr};
	this->nrOfEachItemInventory = new sf::Text * [inventoryCapacity] {nullptr};

	this->drawSkillScreen = false;
	this->skillScreen.setFont(this->fontTwo);
	this->skillScreen.setCharacterSize(20);
	this->skillScreenBackgroundTexture = resourceHandler->getTexture(19);
	this->skillScreenBackground.setTexture(&this->skillScreenBackgroundTexture);
	this->skillScreenBackground.setSize(sf::Vector2f(386.0f, 70.0f));

	this->rectShape.setSize(sf::Vector2f(200, 40));
	this->rectShape.setFillColor(sf::Color::Red);

	this->hpOneBorder.setSize(sf::Vector2f(220, 50));
	this->hpOneBorder.setFillColor(sf::Color::Black);

	this->rectShapeTwo.setSize(sf::Vector2f(200, 40));
	this->rectShapeTwo.setFillColor(sf::Color::Red);

	this->hpTwoBorder.setSize(sf::Vector2f(220, 50));
	this->hpTwoBorder.setFillColor(sf::Color::Black);

	this->HpOne.setFont(this->fontOne);
	this->HpOne.setCharacterSize(40);
	this->HpTwo.setCharacterSize(40);
	this->HpTwo.setFont(this->fontOne);
	this->HpOne.setFillColor(sf::Color::Black);
	this->HpTwo.setFillColor(sf::Color::Black);

	this->CharOneButton = new Clickable(2, resourceHandler);
	this->CharTwoButton = new Clickable(2, resourceHandler);
	
	this->MenyOption.setFont(this->fontTwo);
	this->MenyOption.setCharacterSize(30);
	this->drawMeny = false;

	this->nrOfCraftingOptions = 12;
	this->displayCraftingMeny = false;
	this->displayCraftingMenyInfoBox = false;
	this->craftingMenyOptions = new sf::Text[nrOfCraftingOptions];
	for (int i = 0; i < this->nrOfCraftingOptions; i++)
	{
		this->craftingMenyOptions[i].setFont(this->fontTwo);
		this->craftingMenyOptions[i].setCharacterSize(30);
		this->craftingMenyOptions[i].setFillColor(sf::Color::Black);
	}
	this->craftingMenyOptions[0].setString("Crafting Meny");
	this->craftingMenyOptions[1].setString("Pickaxe");
	this->craftingMenyOptions[2].setString("Axe");
	this->craftingMenyOptions[3].setString("Bucket");
	this->craftingMenyOptions[4].setString("Iron Bar");
	this->craftingMenyOptions[5].setString("Aluminium Bar");
	this->craftingMenyOptions[6].setString("Stone Block");
	this->craftingMenyOptions[7].setString("Furnace");
	this->craftingMenyOptions[8].setString("Water Purifier");
	this->craftingMenyOptions[9].setString("Nail Gun");
	this->craftingMenyOptions[10].setString("Machete");
	this->craftingMenyOptions[11].setString("Electric Machete");

	this->craftingInfoBox.setFont(this->fontTwo);
	this->craftingInfoBox.setCharacterSize(20);
	this->craftingInfoBox.setFillColor(sf::Color::Black);

	this->craftingMenyBackgroundTexture = resourceHandler->getTexture(19);
	this->craftingMenyBackground.setTexture(&this->craftingMenyBackgroundTexture);
	this->craftingMenyBackground.setSize(sf::Vector2f(this->craftingMenyOptions[11].getGlobalBounds().width, 730));

	this->staminaBarOne.setSize(sf::Vector2f(200, 30));
	this->staminaBarOne.setFillColor(sf::Color::Green);
	this->staminaBarTwo.setSize(sf::Vector2f(200, 30));
	this->staminaBarTwo.setFillColor(sf::Color::Green);

	this->staminaOne.setFont(this->fontOne);
	this->staminaOne.setCharacterSize(35);
	this->staminaOne.setFillColor(sf::Color::Black);
	this->staminaOne.setOutlineColor(sf::Color::White);
	this->staminaOne.setOutlineThickness(1);
	this->staminaTwo.setOutlineColor(sf::Color::White);
	this->staminaTwo.setOutlineThickness(1);
	this->staminaTwo.setFont(this->fontOne);
	this->staminaTwo.setCharacterSize(35);
	this->staminaTwo.setFillColor(sf::Color::Black);

	this->craftFurnace = false;
	this->craftStoneBrick = false;
	this->craftWaterPurifier = false;
}

UI::~UI()
{
	delete[]this->characters;
	delete[]this->characterInventory;
	for (int i = 0; i < this->nrOfItems; i++)
	{
		delete this->nrOfEachItemInventory[i];
	}
	delete[]this->nrOfEachItemInventory;
	delete[]this->craftingMenyOptions;
	delete this->CharTwoButton;
	delete this->CharOneButton;
}

void UI::addPCToUI(PlayerCharacter* PC)
{
	this->characters[this->nrOfCharacters] = PC;
	this->nrOfCharacters++;
}

void UI::updateUI()
{
	this->updateCharacterGUI();
	this->updateUIPositions();
}

void UI::drawUI(sf::RenderWindow* window)
{
	window->draw(this->characterGUI);
	window->draw(this->hpOneBorder);
	window->draw(this->hpTwoBorder);
	window->draw(this->rectShape);
	window->draw(this->rectShapeTwo);
	window->draw(this->HpOne);
	window->draw(this->HpTwo);
	window->draw(*this->CharOneButton);
	window->draw(*this->CharTwoButton);
	window->draw(this->staminaBarOne);
	window->draw(this->staminaBarTwo);
	window->draw(staminaOne);
	window->draw(staminaTwo);

	if (this->drawMeny)
	{
		window->draw(this->MenyOption);
	}
	if (this->drawInventory)
	{
		window->draw(this->inventoryBackground);
		for (int i = 0; i < this->nrOfItems;i++)
		{
			window->draw(*this->characterInventory[i]);
			window->draw(*this->nrOfEachItemInventory[i]);
		}
	}
	if (this->drawSkillScreen)
	{
		window->draw(this->skillScreenBackground);
		window->draw(this->skillScreen);
	}
	if (this->displayCraftingMeny)
	{
		window->draw(this->craftingMenyBackground);
		for (int i = 0; i < this->nrOfCraftingOptions; i++)
		{
			window->draw(this->craftingMenyOptions[i]);
		}	
	}
	if (this->displayCraftingMenyInfoBox)
	{
		window->draw(this->craftingInfoBox);
	}
}

void UI::openCloseCharacterInventory()
{
	if (this->drawInventory == false)
	{
		this->drawInventory = true;
		if (this->characters[0]->isSelected())
		{
			this->nrOfItems = characters[0]->getNrOfItems();
			if (this->nrOfItems > this->inventoryCapacity)
			{
				this->expand();
			}
			if (this->nrOfItems > 0)
			{
				this->characters[0]->getAllItems(this->characterInventory);
				if (this->nrOfEachItemInventory[0] != nullptr)
				{
					for (int i = 0; i < this->nrOfItems; i++)
					{
						delete this->nrOfEachItemInventory[i];
						nrOfEachItemInventory[i] = nullptr;
					}
				}
				for (int i = 0; i < this->characters[0]->getNrOfItems();i++)
				{
					sf::Text* text;
					text = new sf::Text;

					text->setFont(this->fontTwo);
					text->setCharacterSize(20);
					text->setString(std::to_string(this->characters[0]->getNrOfAnItem(i)));
					text->setFillColor(sf::Color::Black);
					this->nrOfEachItemInventory[i] = text;
				}
			}
		}
		else if (this->characters[1]->isSelected())
		{
			this->nrOfItems = characters[1]->getNrOfItems();
			if (this->nrOfItems > this->inventoryCapacity)
			{
				this->expand();
			}
			if (this->nrOfItems > 0)
			{
				this->characters[1]->getAllItems(this->characterInventory);
				if (this->nrOfEachItemInventory[0] != nullptr)
				{
					for (int i = 0; i < this->nrOfItems; i++)
					{
						delete this->nrOfEachItemInventory[i];
						nrOfEachItemInventory[i] = nullptr;
					}
				}
				for (int i = 0; i < this->characters[1]->getNrOfItems();i++)
				{
					sf::Text* text;
					text = new sf::Text;

					text->setFont(this->fontTwo);
					text->setCharacterSize(20);
					text->setString(std::to_string(this->characters[1]->getNrOfAnItem(i)));
					text->setFillColor(sf::Color::Black);
					this->nrOfEachItemInventory[i] = text;
				}
			}
		}
	}
	else
	{
		this->drawInventory = false;
	}
}

bool UI::getIfInventoryOpen() const
{
	return this->drawInventory;
}

sf::FloatRect UI::getInventoryBackgroundBounds() const
{
	return this->inventoryBackground.getGlobalBounds();
}

void UI::updateInventory()
{
	if (this->characters[0]->isSelected())
	{
		this->nrOfItems = characters[0]->getNrOfItems();
		if (this->nrOfItems > this->inventoryCapacity)
		{
			this->expand();
		}
		if (this->nrOfItems > 0)
		{
			this->characters[0]->getAllItems(this->characterInventory);
			if (this->nrOfEachItemInventory[0] != nullptr)
			{
				for (int i = 0; i < this->nrOfItems; i++)
				{
					delete this->nrOfEachItemInventory[i];
					nrOfEachItemInventory[i] = nullptr;
				}
			}
			for (int i = 0; i < this->characters[0]->getNrOfItems();i++)
			{
				sf::Text* text;
				text = new sf::Text;

				text->setFont(this->fontTwo);
				text->setCharacterSize(20);
				text->setString(std::to_string(this->characters[0]->getNrOfAnItem(i)));
				text->setFillColor(sf::Color::Black);
				this->nrOfEachItemInventory[i] = text;
			}
		}
	}
	else if (this->characters[1]->isSelected())
	{
		this->nrOfItems = characters[1]->getNrOfItems();
		if (this->nrOfItems > this->inventoryCapacity)
		{
			this->expand();
		}
		if (this->nrOfItems > 0)
		{
			this->characters[1]->getAllItems(this->characterInventory);
			if (this->nrOfEachItemInventory[0] != nullptr)
			{
				for (int i = 0; i < this->nrOfItems; i++)
				{
					delete this->nrOfEachItemInventory[i];
					nrOfEachItemInventory[i] = nullptr;
				}
			}
			for (int i = 0; i < this->characters[1]->getNrOfItems();i++)
			{
				sf::Text* text;
				text = new sf::Text;

				text->setFont(this->fontTwo);
				text->setCharacterSize(20);
				text->setString(std::to_string(this->characters[1]->getNrOfAnItem(i)));
				text->setFillColor(sf::Color::Black);
				this->nrOfEachItemInventory[i] = text;
			}
		}

	}
}

void UI::moveToCharOne()
{
	this->camera->setCenter(sf::Vector2f(characters[0]->getPosition().x, characters[0]->getPosition().y));
}

void UI::moveToCharTwo()
{
	this->camera->setCenter(sf::Vector2f(characters[1]->getPosition().x, characters[1]->getPosition().y));
}

Clickable* UI::getButtonOne()
{
	return this->CharOneButton;
}

Clickable* UI::getButtonTwo()
{
	return this->CharTwoButton;
}

void UI::openCloseCharacterSkillScreen()
{
	if (this->drawSkillScreen == false)
	{
		this->drawSkillScreen = true;
		if (this->characters[0]->isSelected())
		{
			this->skillScreen.setString("Level: " + std::to_string(this->characters[0]->getBaseLevel()) +
				"  Melee: " + std::to_string(this->characters[0]->getMeleeLevel()) +
				"  Ranged: " + std::to_string(this->characters[0]->getRangedLevel()) +
				"\nWoodcutting: " + std::to_string(this->characters[0]->getWoodcuttingLevel()) +
				"  Mining: " + std::to_string(this->characters[0]->getMiningLevel()) +
				"  Hunting: " + std::to_string(this->characters[0]->getHuntingLevel()) +
				"\nEngineering: " + std::to_string(this->characters[0]->getEngineeringLevel()) +
				"  Cooking: " + std::to_string(this->characters[0]->getCookingLevel()) +
				"  Construction: " + std::to_string(this->characters[0]->getConstructionLevel()));
		}
		else if (this->characters[1]->isSelected())
		{
			this->skillScreen.setString("Melee: " + std::to_string(this->characters[1]->getMeleeLevel()) +
				"  Ranged: " + std::to_string(this->characters[1]->getRangedLevel()) +
				"  Woodcutting: " + std::to_string(this->characters[1]->getWoodcuttingLevel()) +
				"\nMining: " + std::to_string(this->characters[1]->getMiningLevel()) +
				"  Hunting: " + std::to_string(this->characters[1]->getHuntingLevel()) +
				"  Engineering: " + std::to_string(this->characters[1]->getEngineeringLevel()) +
				"\nCooking: " + std::to_string(this->characters[1]->getCookingLevel()) +
				"  Construction: " + std::to_string(this->characters[1]->getConstructionLevel()));
		}
	}
	else
	{
		this->drawSkillScreen = false;
	}
}

bool UI::getIfSkillScreenOpen() const
{
	return this->drawSkillScreen;
}

sf::FloatRect UI::getSkillSreenBackgroundBounds() const
{
	return this->skillScreenBackground.getGlobalBounds();
}

void UI::updateSkillScreen()
{
	if (this->characters[0]->isSelected())
	{
		this->nrOfItems = characters[0]->getNrOfItems();
		if (this->nrOfItems > this->inventoryCapacity)
		{
			this->expand();
		}
		if (this->nrOfItems > 0)
		{
			this->characters[0]->getAllItems(this->characterInventory);
			if (this->nrOfEachItemInventory[0] != nullptr)
			{
				for (int i = 0; i < this->nrOfItems; i++)
				{
					delete this->nrOfEachItemInventory[i];
					nrOfEachItemInventory[i] = nullptr;
				}
			}
			for (int i = 0; i < this->characters[0]->getNrOfItems();i++)
			{
				sf::Text* text;
				text = new sf::Text;

				text->setFont(this->fontTwo);
				text->setCharacterSize(20);
				text->setString(std::to_string(this->characters[0]->getNrOfAnItem(i)));
				text->setFillColor(sf::Color::Black);
				this->nrOfEachItemInventory[i] = text;
			}
		}
	}
	else if (this->characters[1]->isSelected())
	{
		this->nrOfItems = characters[1]->getNrOfItems();
		if (this->nrOfItems > this->inventoryCapacity)
		{
			this->expand();
		}
		if (this->nrOfItems > 0)
		{
			this->characters[1]->getAllItems(this->characterInventory);
			if (this->nrOfEachItemInventory[0] != nullptr)
			{
				for (int i = 0; i < this->nrOfItems; i++)
				{
					delete this->nrOfEachItemInventory[i];
					nrOfEachItemInventory[i] = nullptr;
				}
			}
			for (int i = 0; i < this->characters[0]->getNrOfItems();i++)
			{
				sf::Text* text;
				text = new sf::Text;

				text->setFont(this->fontTwo);
				text->setCharacterSize(20);
				text->setString(std::to_string(this->characters[0]->getNrOfAnItem(i)));
				text->setFillColor(sf::Color::Black);
				this->nrOfEachItemInventory[i] = text;
			}
		}

	}
}


void UI::unstuckCamera()
{
	//if (camera->getCenter().x < window->getPosition().x / 4)
	//{
	//	camera->move(5, 0);
	//}
	//else if (camera->getCenter().x > (window->getPosition().x / 4) * 3)
	//{
	//	camera->move(-5, 0);
	//}
	//if (camera->getCenter().y < window->getPosition().y / 4)
	//{
	//	camera->move(0, 5);
	//}
	//else if (camera->getCenter().y > (window->getPosition().y / 4) * 3)
	//{
	//	camera->move(0, -5);
	//}
}

void UI::displayMeny(ResourceTile* tileToDisplay, const sf::Vector2f& position)
{
	if (tileToDisplay->getName() == "Aluminium Deposit")
	{
		this->MenyOption.setString("Mine Aluminium");
	}
	else if (tileToDisplay->getName() == "Coal Deposit")
	{
		this->MenyOption.setString("Mine Coal");
	}
	else if (tileToDisplay->getName() == "Iron Deposit")
	{
		this->MenyOption.setString("Mine Iron");
	}
	else if (tileToDisplay->getName() == "Stone Deposit")
	{
		this->MenyOption.setString("Mine Stone");
	}
	else if (tileToDisplay->getName() == "Tree")
	{
		this->MenyOption.setString("Cut Tree");
	}
	else if (tileToDisplay->getName() == "Water")
	{
		this->MenyOption.setString("Gather Water");
	}
	else if (tileToDisplay->getName() == "Poisoned Water")
	{
		this->MenyOption.setString("Purify Water");
	}
	else if (tileToDisplay->getName() == "Battery")
	{
		this->MenyOption.setString("Pick up Battery");
	}
	this->MenyOption.setPosition(position);
}

void UI::openCloseMeny(bool trigger)
{
	this->drawMeny = trigger;
}

bool UI::getIfMenyDrawn() const
{
	return this->drawMeny;
}

sf::Vector2f UI::getMenyPosition() const
{
	return this->MenyOption.getPosition();
	
}

sf::FloatRect UI::getMenyBounds() const
{
	return this->MenyOption.getGlobalBounds();
}

void UI::openCloseCraftingMeny()
{
	if (this->displayCraftingMeny == false)
	{
		this->displayCraftingMeny = true;
	}
	else
	{
		this->displayCraftingMeny = false;
		this->displayCraftingMenyInfoBox = false;
	}
}

bool UI::getIfCraftingMenyOpen()const
{
	return this->displayCraftingMeny;
}

sf::FloatRect UI::getCraftingMenyBounds(const int index)
{
	return this->craftingMenyOptions[index].getGlobalBounds();
}

void UI::displayCraftingInfoBox(const int index)
{
	this->displayCraftingMenyInfoBox = true;
	if (index == 1)
	{
		this->craftingInfoBox.setString("2 Logs\n1 Iron Bar");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[1].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[1].getPosition().y);
	}
	else if (index == 2)
	{
		this->craftingInfoBox.setString("2 Logs\n1 Iron Bar");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[2].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[2].getPosition().y);
	}
	else if (index == 3)
	{
		this->craftingInfoBox.setString("2 Logs");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[3].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[3].getPosition().y);
	}
	else if (index == 4)
	{
		this->craftingInfoBox.setString("3 Iron Ore");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[4].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[4].getPosition().y);
	}
	else if (index == 5)
	{
		this->craftingInfoBox.setString("3 Aluminium Ore");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[5].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[5].getPosition().y);
	}
	else if (index == 6)
	{
		this->craftingInfoBox.setString("3 Stone Ore");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[6].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[6].getPosition().y);
	}
	else if (index == 7)
	{
		this->craftingInfoBox.setString("3 Stone Block");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[7].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[7].getPosition().y);
	}
	else if (index == 8)
	{
		this->craftingInfoBox.setString("1 Iron bar\n3 Aluminium Bar\n1 Battery");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[8].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[8].getPosition().y);
	}
	else if (index == 9)
	{
		this->craftingInfoBox.setString("2 Iron Bar\n3 Aluminium Bar");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[9].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[9].getPosition().y);
	}
	else if (index == 10)
	{
		this->craftingInfoBox.setString("3 Iron Bar\n1 Log");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[10].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[10].getPosition().y);
	}
	else if (index == 11)
	{
		this->craftingInfoBox.setString("1 Machete\n 1 Battery");
		this->craftingInfoBox.setPosition(this->craftingMenyOptions[11].getPosition().x - this->craftingInfoBox.getGlobalBounds().width - 20, this->craftingMenyOptions[11].getPosition().y);
	}
}

void UI::closeCraftingMenyInfoBox()
{
	this->displayCraftingMenyInfoBox = false;
}

sf::FloatRect UI::getCraftingMenyBackgroundBounds() const
{
	return this->craftingMenyBackground.getGlobalBounds();
}

void UI::interactWithInventory(sf::Vector2f mouseClickPosition)
{
	int itemSelected = -1;
	for (int i = 0; i < this->nrOfItems; i++)
	{
		if (this->characterInventory[i]->getBounds().contains(mouseClickPosition))
		{
			itemSelected = i;
			i = this->nrOfItems;
		}
	}
	if (itemSelected != -1)
	{
		if (this->characterInventory[itemSelected]->getIfWeapon() == true)
		{
			if (this->characters[0]->isSelected())
			{
				this->characters[0]->equipWeapon(this->characterInventory[itemSelected]);
			}
			else if (this->characters[1]->isSelected())
			{
				this->characters[1]->equipWeapon(this->characterInventory[itemSelected]);
			}
		}
		else if (this->characterInventory[itemSelected]->getName() == "Furnace")
		{
			this->updateCraftFurance(1);
		}
		else if (this->characterInventory[itemSelected]->getName() == "Water Purifier")
		{
			this->updateCraftWaterPurifier(1);
		}
		else if (this->characterInventory[itemSelected]->getName() == "Stone Block")
		{
			this->updateCraftStoneBrick(1);
		}
	}
}

void UI::updateCraftFurance(int state)
{
	if (state == 0)
	{
		this->craftFurnace = false;
	}
	else if (state == 1)
	{
		this->craftFurnace = true;
	}
}

void UI::updateCraftWaterPurifier(int state)
{
	if (state == 0)
	{
		this->craftWaterPurifier = false;
	}
	else if (state == 1)
	{
		this->craftWaterPurifier = true;
	}
}

void UI::updateCraftStoneBrick(int state)
{
	if (state == 0)
	{
		this->craftStoneBrick = false;
	}
	else if (state == 1)
	{
		this->craftStoneBrick = true;
	}
}

bool UI::stateOfCraft(int type)
{
	bool typeReturn = false;

	if (type == 1)
	{
		typeReturn = craftFurnace;
	}
	else if (type == 2)
	{
		typeReturn = craftWaterPurifier;
	}
	else if (type == 3)
	{
		typeReturn = craftStoneBrick;
	}

	return typeReturn;
}
