#pragma once
#ifndef CLICKABLE_H
#define CLICKABLE_H
#include "SFML/Graphics.hpp"
#include "Reshandler.h"
#include <string>

class Clickable : public sf::Drawable
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	bool m_active;

	bool isInside(const sf::Vector2f &mousePosF)const;
protected:
	void moveSprite(const int horDir, const int vertDir, float speed);
	void updateSprite(int id, ResHandler* resourceHandler);
public:
	void reset();
	Clickable();
	Clickable(const int index, ResHandler* resourceHandler);
	Clickable(const int index, ResHandler* resourceHandler, float x, float y);

	sf::FloatRect getBounds()const;
	bool click(const sf::Vector2f& mousePosF);
	bool collision(const Clickable &otherObject)const;
	void setCoordinates(float xPos, float yPos);
	void setTextureRect(const sf::IntRect intRect);
	sf::Vector2f getPosition()const;
	sf::Vector2u getTextureSize()const;
	void setSpriteScale(float x, float y);
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
#endif // !CLICKABLE_H
