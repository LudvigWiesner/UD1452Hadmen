#include "UI.h"

void UI::updateCharacterGUI()
{
	//this->characterGUI.setString("");
	//for (int i = 0; i < this->nrOfCharacters; i++)
	//{
	//	this->characterGUI.setString(this->characterGUI.getString() +
	//		std::to_string(this->characters[i]->getMaxHP()) + "/" + std::to_string(this->characters[i]->getCurrentHP()) + "\n");
	//}
	
	
	this->rectShape.setSize(sf::Vector2f(this->characters[0]->getCurrentHP() * 2, 40));
	this->rectShapeTwo.setSize(sf::Vector2f(this->characters[1]->getCurrentHP() * 2, 40));
	this->HpOne.setString(std::to_string(characters[0]->getMaxHP()) + "/" + std::to_string(this->characters[0]->getCurrentHP()));
	this->HpTwo.setString(std::to_string(characters[1]->getMaxHP()) + "/" + std::to_string(this->characters[1]->getCurrentHP()));

}
void UI::updateUIPositions()
{
	/*this->characterGUI.setPosition(5 + camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2);*/
	this->inventoryBackground.setPosition(camera->getCenter().x - this->inventoryBackground.getGlobalBounds().width + window->getSize().x / 2, camera->getCenter().y + 20 - window->getSize().y / 2);
	if (this->drawInventory && this->nrOfItems > 0)
	{
		for (int i = 0; i < this->nrOfItems; i++)
		{
			this->characterInventory[i].setCoordinates(camera->getCenter().x, camera->getCenter().y);
		}
	}

	this->rectShape.setPosition(40 + camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2 + 40);
	this->rectShapeTwo.setPosition(rectShape.getPosition().x, rectShape.getPosition().y + 60);

	this->hpOneBorder.setPosition(rectShape.getPosition().x - 10, rectShape.getPosition().y - 5);
	this->hpTwoBorder.setPosition(rectShapeTwo.getPosition().x - 10, rectShapeTwo.getPosition().y - 5);

	this->CharOneButton.setPosition(rectShape.getPosition().x + 225, rectShape.getPosition().y);
	this->CharTwoButton.setPosition(CharOneButton.getPosition().x, rectShapeTwo.getPosition().y);

	this->HpOne.setPosition(rectShape.getPosition().x + 30, rectShape.getPosition().y - 8);
	this->HpTwo.setPosition(rectShapeTwo.getPosition().x + 30, rectShapeTwo.getPosition().y - 8);

}

void UI::expand()
{
	Item* temp;
	this->inventoryCapacity= this->inventoryCapacity * 2;

	temp = new Item [this->inventoryCapacity];
	for (int i = 0; i < this->nrOfItems;i++)
	{
		temp[i] = this->characterInventory[i];
	}
	delete[]this->characterInventory;
	this->characterInventory = temp;
	temp = nullptr;
}


UI::UI(sf::RenderWindow* window, sf::View* camera, ResHandler* resourceHandler)
{
	this->window = window;
	this->camera = camera;
	this->fontOne.loadFromFile("../images/TrenchThin-aZ1J.ttf");
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
	this->inventoryBackground.setSize(sf::Vector2f(400.0f, 800.0f));
	this->inventoryBackground.setPosition(camera->getCenter().x - this->inventoryBackground.getGlobalBounds().width + window->getSize().x / 2,
		camera->getCenter().y + 20 - window->getSize().y / 2);

	this->inventoryCapacity = 20;
	this->nrOfItems = 0;
	this->characterInventory = new Item[inventoryCapacity];


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

		this->CharOneButton.setSize(sf::Vector2f(40, 40));
		this->CharOneButton.setFillColor(sf::Color::Black);
		this->CharOneButton.setOutlineThickness(2);
		this->CharOneButton.setOutlineColor(sf::Color (169,169,169));

		this->CharTwoButton.setSize(sf::Vector2f(40, 40));
		this->CharTwoButton.setFillColor(sf::Color::Black);
		this->CharTwoButton.setOutlineThickness(2);
		this->CharTwoButton.setOutlineColor(sf::Color(169, 169, 169));
		
}

UI::~UI()
{
	delete[]this->characters;
	delete[]this->characterInventory;
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

void UI::moveToProfile()
{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && CharOneButton.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
		{
			this->camera->setCenter(sf::Vector2f(characters[0]->getPosition().x, characters[0]->getPosition().y));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && CharTwoButton.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
		{
			this->camera->setCenter(sf::Vector2f(characters[1]->getPosition().x, characters[1]->getPosition().y));
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

void UI::drawUI(sf::RenderWindow* window)
{
	window->draw(this->characterGUI);
	if (this->drawInventory)
	{
		window->draw(this->inventoryBackground);
		for (int i = 0; i < this->nrOfItems;i++)
		{
			window->draw(this->characterInventory[i]);
		}
	}

	window->draw(this->hpOneBorder);
	window->draw(this->hpTwoBorder);
	window->draw(this->rectShape);
	window->draw(this->rectShapeTwo);
	window->draw(this->HpOne);
	window->draw(this->HpTwo);
	window->draw(this->CharOneButton);
	window->draw(this->CharTwoButton);
	
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
			}
			
		}
	}
	else
	{
		this->drawInventory = false;
	}

}
