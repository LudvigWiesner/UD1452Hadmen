#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TileEntity :public sf::Drawable
{
private:
	sf::Texture tileTexture;
	sf::Sprite	tileSprite;
	//bool collision;
public:
	TileEntity();
	TileEntity(const std::string filename);
	~TileEntity();

	//bool collision();
	//void setCollision(bool state);

	void setCoordinates(float xPos, float yPos);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};