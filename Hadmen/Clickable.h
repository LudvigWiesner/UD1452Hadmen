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

	bool m_pressed;
	bool m_mouseHeld;
	bool m_active;

	bool isInside(const sf::RenderWindow& window)const;
	void reset();
public:
	Clickable();
	Clickable(const int index, ResHandler* resourceHandler);
	Clickable(const int index, ResHandler* resourceHandler, float x, float y);

	sf::FloatRect getBounds()const;
	bool click(const sf::RenderWindow& window, const sf::Event& event);
	bool collision(const Clickable &otherObject)const;
	void setCoordinates(float xPos, float yPos);
	void setTextureRect(const sf::IntRect intRect);
	void moveSprite(const int horDir, const int vertDir);
	sf::Vector2f getPosition()const;
	sf::Vector2u getTextureSize()const;
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
#endif // !CLICKABLE_H
