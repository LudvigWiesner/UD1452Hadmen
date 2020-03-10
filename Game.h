#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Reshandler.h"
#include "ItemHandler.h"
#include "PlayerCharacter.h"
#include "UI.h"
#include "Melee.h"
#include "Ranged.h"
#include "Boss.h"
#include "Furnace.h"
#include "WaterPurifier.h"
#include "StoneBrick.h"
#include "Sound.h"

class Game : public GameState
{
private:
	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate;
	sf::Time timePerFrame;

	sf::Image baseImage;
	sf::View* camera;

	TileMap* tileMap;
	ResHandler resourceHandler;

	PlayerCharacter* PCOne;
	PlayerCharacter* PCTwo;
	sf::Vector2i mouseClickWindowPosition;
	sf::Vector2f mouseWorldCoordinates;
	sf::Vector2f playerGoToCoordinates;

	UI* userInterface;

	Melee* Wei;
	Ranged* Wei2;
	Boss* Wei3;

	TileEntity* selectedTile;
	ResourceTile* castPtr;

	Furnace* furnace;
	WaterPurifier* waterPlant;
	StoneBrick* stonebrick[10];

	//SoundEffect furnaceSound;

	int maxStoneBricks;
	int currentBricks;
public:
	Game(float windowWidth, float windowHeight);
	virtual ~Game();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;

};