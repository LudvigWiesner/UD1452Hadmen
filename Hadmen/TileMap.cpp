#include "TileMap.h"

TileMap::TileMap(sf::Image& tileRef, ResHandler* resourceHandler)
	:tileSize(50.0f)
{
	arrBackgrounds = new TileEntity * *[TILEMAPSIZE];
	for (int i = 0; i < TILEMAPSIZE; i++)
	{
		arrBackgrounds[i] = new TileEntity * [TILEMAPSIZE];
	}

	this->mapRef = tileRef;//for pixel cheeck

	for (int Y = 0; Y < TILEMAPSIZE; Y++)
	{
		for (int X = 0; X < TILEMAPSIZE; X++)
		{
			if (this->mapRef.getPixel(X, Y) == sf::Color::Color(204, 204, 204))
			{
				arrBackgrounds[X][Y] = new ResourceTile(0, resourceHandler, "Aluminium Deposit", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 0, 0))
			{
				arrBackgrounds[X][Y] = new ResourceTile(1, resourceHandler, "Coal Deposit", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(03, 00, 148))
			{
				arrBackgrounds[X][Y] = new ResourceTile(8, resourceHandler, "Water", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(153, 102, 102))
			{
				arrBackgrounds[X][Y] = new ResourceTile(2, resourceHandler, "Iron Deposit", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 102, 0))
			{
				arrBackgrounds[X][Y] = new ResourceTile(6, resourceHandler, "Tree", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(196, 196, 196))
			{
				arrBackgrounds[X][Y] = new ResourceTile(5, resourceHandler, "Stone Deposit", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(204, 153, 0)) // Dirt
			{
				arrBackgrounds[X][Y] = new TileEntity(13, resourceHandler, X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(153, 0, 0)) // Wall
			{
				arrBackgrounds[X][Y] = new TileEntity(7, resourceHandler, X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 148, 0)) // Grass
			{
				arrBackgrounds[X][Y] = new TileEntity(14, resourceHandler, X * 50.0f, Y * 50.0f);
			}
			else
			{
				arrBackgrounds[X][Y] = new TileEntity(12, resourceHandler, X * 50.0f, Y * 50.0f); // Gravel
			}
		}
	}
}


TileMap::~TileMap()
{
	for (int Y = 0; Y < TILEMAPSIZE; Y++)
	{
		for (int X = 0; X < TILEMAPSIZE; X++)
		{
			delete arrBackgrounds[X][Y];
			
		}
	}
	for (int i = 0; i < TILEMAPSIZE; i++)
	{
		delete[] arrBackgrounds[i];
	}
		delete[] arrBackgrounds;
}

void TileMap::renderTileMap(sf::RenderWindow& targetWindow)
{
	for (int Y = 0; Y < TILEMAPSIZE; Y++)
	{
		for (int X = 0; X < TILEMAPSIZE; X++)
		{
			targetWindow.draw(*this->arrBackgrounds[X][Y]);
		}
	}
}

TileEntity* TileMap::getTile(int x, int y)
{
	return arrBackgrounds[x][y];
}
