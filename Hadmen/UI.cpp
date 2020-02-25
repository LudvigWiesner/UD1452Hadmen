#include "UI.h"

void UI::updateCharacterGUI()
{
	this->characterGUI.setString("");
	for (int i = 0; i < this->nrOfCharacters; i++)
	{
		this->characterGUI.setString(this->characterGUI.getString() +
			std::to_string(this->characters[i]->getMaxHP()) + "/" + std::to_string(this->characters[i]->getCurrentHP()) + "\n");
	}
}
void UI::updateUIPositions()
{
	this->characterGUI.setPosition(5 + camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2);
	this->inventoryBackground.setPosition(camera->getCenter().x - this->inventoryBackground.getGlobalBounds().width + window->getSize().x / 2, camera->getCenter().y + 20 - window->getSize().y / 2);
}

void UI::expand()
{
	Item** temp;
	this->inventoryCapacity= this->inventoryCapacity * 2;

	temp = new Item * [this->inventoryCapacity];
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

	this->inventoryCapacity = 40;
	this->nrOfItems = 0;
	this->characterInventory = new Item * [inventoryCapacity];
}

UI::~UI()
{
	delete[]this->characters;
	for (int i = 0; i < this->nrOfItems; i++)
	{
		delete this->characterInventory[i];
	}
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

void UI::drawUI(sf::RenderWindow* window)
{
	window->draw(this->characterGUI);
	if (this->drawInventory)
	{
		window->draw(this->inventoryBackground);
	}
	
}

void UI::openCloseCharacterInventory()
{
	if (this->drawInventory == false)
	{
		this->drawInventory = true;
		if (this->characters[0]->isSelected())
		{
			if (this->characters[0]->getNrOfItems() > this->inventoryCapacity)
			{
				this->expand();
			}
			this->nrOfItems = characters[0]->getNrOfItems();
			this->characters[0]->getAllItems(*this->characterInventory);
			//for (int i = 0; i < this->nrOfItems; i++)
			//{
			//	this->characterInventory[i]->setCoordinates()
			//}
		}
		else if (this->characters[1]->isSelected())
		{
			if (this->characters[1]->getNrOfItems() > this->inventoryCapacity)
			{
				this->expand();
			}
			this->nrOfItems = characters[1]->getNrOfItems();
			this->characters[1]->getAllItems(*this->characterInventory);
		}
	}
	else
	{
		this->drawInventory = false;
	}

}
