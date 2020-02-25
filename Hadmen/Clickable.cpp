#include "Clickable.h"

Clickable::Clickable()
{
	this->m_pressed = false;
	this->m_mouseHeld = false;
	this->m_active = false;
}

Clickable::Clickable(const int index, ResHandler* resourceHandler)
{
	this->m_pressed = false;
	this->m_mouseHeld = false;
	this->m_active = false;
	this->texture = resourceHandler->getTexture(index);
	this->sprite.setTexture(this->texture);
}

Clickable::Clickable(const int index, ResHandler* resourceHandler, float x, float y)
{
	this->m_pressed = false;
	this->m_mouseHeld = false;
	this->m_active = false;
	this->texture = resourceHandler->getTexture(index);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(x, y);
}

sf::FloatRect Clickable::getBounds()const
{
	return this->sprite.getGlobalBounds();
}

bool Clickable::isInside(const sf::RenderWindow& window) const
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	return this->sprite.getGlobalBounds().contains(mousePosF);
}

void Clickable::reset()
{
	this->m_active = false;
}

bool Clickable::click(const sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && this->isInside(window) && !this->m_mouseHeld)
	{
		this->m_pressed = true;
		this->m_mouseHeld = true;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		this->m_mouseHeld = true;
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (this->isInside(window) && this->m_pressed)
		{
			this->m_active = true;
		}
		this->m_pressed = false;
		this->m_mouseHeld = false;
	}
	return this->m_active;
}

bool Clickable::collision(const Clickable &otherObject)const
{
	return this->sprite.getGlobalBounds().intersects(otherObject.getBounds());
}

void Clickable::setCoordinates(float xPos, float yPos)
{
	this->sprite.setPosition(xPos, yPos);
}

void Clickable::setTextureRect(const sf::IntRect intRect)
{
	this->sprite.setTextureRect(intRect);
}

void Clickable::moveSprite(const int horDir, const int vertDir, float speed) // Speed need to be added
{
	this->sprite.move(horDir * speed, vertDir * speed);
}

sf::Vector2f Clickable::getPosition() const
{
	return this->sprite.getPosition();
}

sf::Vector2u Clickable::getTextureSize() const
{
	return this->texture.getSize();
}

void Clickable::setSpriteScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

void Clickable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}