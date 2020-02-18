#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Reshandler.h"

class TileEntity :public sf::Drawable
{
private:
	sf::Texture tileTexture;
	sf::Sprite	tileSprite;
public:
	TileEntity();
	TileEntity(const int index, ResHandler *resourceHandler);
	~TileEntity();


	void setCoordinates(float xPos, float yPos);
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};