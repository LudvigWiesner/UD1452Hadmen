#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class GameOver : public GameState
{
public:
	static const int HEIGHT = 600;
	static const int WIDTH = 900;
private:


public:
	GameOver();
	virtual ~GameOver();
	void run();


	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};