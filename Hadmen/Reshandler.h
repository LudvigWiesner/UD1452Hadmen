#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#ifndef RESHANDLER_H
#define RESHANDLER_H

class ResHandler
{
private:
	sf::Texture* textures;
	int size = 20;
public:
	ResHandler();
	~ResHandler();

	sf::Texture getTexture(const int index);
};
#endif // !RESHANDLER_H
