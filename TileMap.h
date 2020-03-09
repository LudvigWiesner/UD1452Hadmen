#pragma once
#include "TileEntity.h"
#include "ResourceTile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
const int TILEMAPSIZE = 108;

class TileMap
{
private:
	sf::Image mapRef;
	TileEntity*** arrBackgrounds;
	float tileSize;
	//TileEntity* arrResNCharObj[TILEMAPSIZE][TILEMAPSIZE];
	//TileEntity* arrCharacterObj[TILEMAPSIZE][TILEMAPSIZE];

public:
	TileMap(sf::Image &tileRef, ResHandler* resourceHandler);
	virtual ~TileMap();

	void renderTileMap(sf::RenderWindow &targetWindow);
	TileEntity* getTile(int x, int y);
	TileEntity* getTileType(int x, int y);
};