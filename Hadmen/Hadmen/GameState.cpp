#include "GameState.h"

GameState::GameState(std::string title, float windowWidth, float windowHeight)	: window(sf::VideoMode(windowWidth, windowHeight), title)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

GameState::~GameState()
{
}
