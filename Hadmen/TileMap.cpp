#include "TileMap.h"
#include "iostream"

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
			if (this->mapRef.getPixel(X, Y) == sf::Color::Color(55, 193, 25))
			{
				
				arrBackgrounds[X][Y] = new TileEntity(7, resourceHandler, X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(146, 146, 146))
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
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(19, 19, 19))
			{
				arrBackgrounds[X][Y] = new ResourceTile(2, resourceHandler, "Iron Deposit", X * 50.0f, Y * 50.0f);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 148, 0))
			{
				arrBackgrounds[X][Y] = new TileEntity(14, resourceHandler, X * 50.0f, Y * 50.0f);
			}
			else
			{

				arrBackgrounds[X][Y] = new TileEntity(6, resourceHandler, X * 50.0f, Y * 50.0f);

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
	return *arrBackgrounds[x, y];
}
