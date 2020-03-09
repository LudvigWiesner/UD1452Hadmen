#pragma once
#include "SFML/Graphics.hpp"
#ifndef RESHANDLER_H
#define RESHANDLER_H

class ResHandler
{
private:
	sf::Texture* textures;
	int texturesSize = 30;

public:
	ResHandler();
	~ResHandler();

	sf::Texture getTexture(const int index);
};
#endif // !RESHANDLER_H
