#include "startMeny.h"
#include <iostream>

void StartMeny::moveUp()
{
	if (this->selected > 0)
	{
		this->alternatives[selected].setFillColor(sf::Color::Yellow);
		this->selected--;
		this->alternatives[selected].setFillColor(sf::Color::Red);
	}
}
void StartMeny::moveDown()
{
	if (this->selected < 1)
	{
		this->alternatives[selected].setFillColor(sf::Color::Yellow);
		this->selected++;
		this->alternatives[selected].setFillColor(sf::Color::Red);
	}
}

StartMeny::StartMeny(float windowWidth, float windowHeight) : GameState("StartMeny", windowWidth, windowHeight)
{
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	alternatives[0].setFont(font);
	alternatives[0].setFillColor(sf::Color::Red);
	alternatives[0].setCharacterSize(30);
	alternatives[0].setString("Play");
	alternatives[0].setPosition(200.f, 200.f);

	alternatives[1].setFont(font);
	alternatives[1].setFillColor(sf::Color::Yellow);
	alternatives[1].setCharacterSize(30);
	alternatives[1].setString("Exit");
	alternatives[1].setPosition(200.f, 350.f);


	selected = 0;
	done = false;
}

StartMeny::~StartMeny()
{
}

State StartMeny::update()
{

	State state = State::NO_CHANGE;
	if (done)
	{
		if (selected == 0)
		{
			state = State::PLAY;
		}
		else if (selected == 1)
		{
			state = State::EXIT;
		}
	}

	return state;
}

void StartMeny::render()
{
	window.clear();
	for (int i = 0; i < 2; i++)
	{
		window.draw(alternatives[i]);
	}
	window.display();
}

void StartMeny::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				this->moveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				this->moveDown();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				this->done = true;
			}
		}
	}
}