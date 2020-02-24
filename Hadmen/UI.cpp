#include "UI.h"

void UI::updateCharacterGUI()
{
	//this->characterGUI.setString(std::to_string(this->characters[0]->getCurrentHP()) + "/" + std::to_string(this->characters[0]->getMaxHP()));
	//this->characterGUI.setPosition(camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2);

	this->characterGUI.setString("");
	for (int i = 0; i < this->nrOfCharacters; i++)
	{
		this->characterGUI.setString(this->characterGUI.getString() +
			std::to_string(this->characters[i]->getMaxHP()) + "/" + std::to_string(this->characters[i]->getCurrentHP()) + "\n");
	}
	this->characterGUI.setPosition(5 + camera->getCenter().x - window->getSize().x / 2, camera->getCenter().y - window->getSize().y / 2);
	
} 

UI::UI(sf::RenderWindow* window, sf::View* camera)
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
}

UI::~UI()
{
	delete[]this->characters;
}

void UI::addPCToUI(PlayerCharacter* PC)
{
	this->characters[this->nrOfCharacters] = PC;
	this->nrOfCharacters++;
}

void UI::updateUI()
{
	this->updateCharacterGUI();
}

void UI::drawUI(sf::RenderWindow* window)
{
	window->draw(this->characterGUI);
}
