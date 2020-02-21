#include "startMeny.h"
#include <iostream>

StartMeny::StartMeny(float windowWidth, float windowHeight) : GameState("StartMeny", windowWidth, windowHeight)
{
	font.loadFromFile("../images/TrenchThin-aZ1J.ttf");
	alternatives[0].setFont(font);
	alternatives[0].setFillColor(sf::Color::Red);
	alternatives[0].setCharacterSize(60);
	alternatives[0].setString("Play");
	alternatives[0].setPosition(windowWidth / 2 - alternatives[0].getGlobalBounds().width / 2, windowHeight / 2 - 150);

	alternatives[1].setFont(font);
	alternatives[1].setFillColor(sf::Color::Yellow);
	alternatives[1].setCharacterSize(60);
	alternatives[1].setString("Exit");
	alternatives[1].setPosition(windowWidth / 2 - alternatives[1].getGlobalBounds().width / 2, windowHeight / 2);

	backgroundTexture.loadFromFile("../Images/backgroundImage.jpg");
	backgroundImage.setTexture(backgroundTexture);

	backgroundImage.setScale(windowWidth / backgroundImage.getLocalBounds().width, windowHeight / backgroundImage.getLocalBounds().height);
	selected = 0;
	done = false;
	
	music.setMusic("backgroundMusicTwo");
	music.changeVolume(20);
	music.playMusic();
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
			music.stopMusic();
		}
	}

	return state;
}

void StartMeny::render()
{
	window.clear();
	window.draw(backgroundImage);
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
		switch(event.type)
		{
		case sf::Event::Closed:
			window.close();
		break;

		case sf::Event::MouseMoved:
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			if (this->alternatives[0].getGlobalBounds().contains(mousePosF))
			{
				this->alternatives[0].setFillColor(sf::Color::Yellow);
			}
			else
			{
				this->alternatives[0].setFillColor(sf::Color::Red);
			}
			if (this->alternatives[1].getGlobalBounds().contains(mousePosF))
			{
				this->alternatives[1].setFillColor(sf::Color::Yellow);
			}
			else
			{
				this->alternatives[1].setFillColor(sf::Color::Red);
			}
		}
		break;

		case sf::Event::MouseButtonPressed:
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			if (this->alternatives[0].getGlobalBounds().contains(mousePosF))
			{
				this->selected = 0;
				this->done = true;
			}
			else if(this->alternatives[1].getGlobalBounds().contains(mousePosF))
			{
				this->selected = 1;
				this->done = true;
			}
		}
		break;
			
		}
	}
}