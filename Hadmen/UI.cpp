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
	else
	{
		this->drawInventory = false;
	}

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