#pragma once
#ifndef CLICKABLE_H
#define CLICKABLE_H
#include "SFML/Graphics.hpp"
#include "Reshandler.h"
#include <string>

class Clickable : public sf::Drawable
{
private:
	std::string fileName;
	sf::Sprite sprite;
	sf::Texture texture;

	bool m_pressed;
	bool m_mouseHeld;
	bool m_active;

	bool isInside(const sf::RenderWindow& window)const;
	void reset();
public:
	Clickable(const int index, ResHandler* resourceHandler);
	sf::FloatRect getBounds()const;
	bool click(const sf::RenderWindow& window, const sf::Event& event);
	bool collision(const Clickable &otherObject)const;
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
#endif // !CLICKABLE_H
