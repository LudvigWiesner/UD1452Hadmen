#include "Clickable.h"

Clickable::Clickable()
{
	this->m_active = false;
}

Clickable::Clickable(const int index, ResHandler* resourceHandler)
{
	this->m_active = false;
	this->texture = resourceHandler->getTexture(index);
	this->sprite.setTexture(this->texture);
}

Clickable::Clickable(const int index, ResHandler* resourceHandler, float x, float y)
{
	this->m_active = false;
	this->texture = resourceHandler->getTexture(index);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(x, y);
}

Clickable::Clickable(const Clickable &otherClickable)
{
	this->m_active = otherClickable.m_active;
	this->texture = otherClickable.texture;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(otherClickable.getPosition());
}

sf::FloatRect Clickable::getBounds()const
{
	return this->sprite.getGlobalBounds();
}

bool Clickable::isInside(const sf::Vector2f &mousePosF) const
{
	return this->sprite.getGlobalBounds().contains(mousePosF);
}

void Clickable::reset()
{
	this->m_active = false;
}

bool Clickable::click(const sf::Vector2f &mousePosF)
{
	if (this->isInside(mousePosF))
	{
		this->m_active = true;
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

void Clickable::moveSprite(const int horDir, const int vertDir, float speed)
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

void Clickable::setTexture(const int index, ResHandler* resourceHandler)
{
	this->texture = resourceHandler->getTexture(index);
	this->sprite.setTexture(this->texture);
}

void Clickable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
