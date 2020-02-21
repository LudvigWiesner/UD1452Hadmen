#pragma once
#include"GameState.h"
#include "Music.h"

class StartMeny : public GameState
{
private:
	sf::Text alternatives[2];
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundImage;

	Music music;

	int selected;
	bool done;

public:
	StartMeny(float windowWidth, float windowHeight);
	virtual ~StartMeny();

	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};