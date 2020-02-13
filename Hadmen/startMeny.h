#pragma once
#include"GameState.h"

class StartMeny : public GameState
{
private:
	sf::Text alternatives[2];
	sf::Font font;

	int selected;
	bool done;

	void moveUp();
	void moveDown();
public:
	StartMeny();
	virtual ~StartMeny();

	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};