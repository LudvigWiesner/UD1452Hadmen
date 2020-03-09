#include "GameOver.h"

GameOver::GameOver(float windowWidth, float windowHeight) : GameState("GameOver", windowWidth, windowHeight)
{
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	labelText.setFont(font);
	labelText.setPosition(50.f, 50.f);
	labelText.setFillColor(sf::Color::Green);
	labelText.setCharacterSize(30);
	labelText.setString("Input name (<enter> when done)");

	text.setFont(font);
	text.setPosition(200.f, 200.f);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(30);
	name = "";

	text.setString(name);
	done = false;
}

GameOver::~GameOver()
{
}

State GameOver::update()
{
	State state = State::NO_CHANGE;
	if (done)
	{
		state = State::MENU;
	}
	return state;
}

void GameOver::render()
{
	window.clear();
	window.draw(this->labelText);
	window.draw(this->text);
	window.display();
}

void GameOver::handleEvents()
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				this->done = true;
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					if (this->name.length() > 0)
					{
						this->name.erase(name.length() - 1, 1);
					}
				}
				else if (event.text.unicode >= 0 && event.text.unicode <= 25)
				{
					this->name += (char)(event.text.unicode + 65);
				}

			}
			this->text.setString(name);

		}
	}
}
