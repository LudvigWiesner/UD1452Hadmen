#include "TileMap.h"

TileMap::TileMap(sf::Image &tileRef)
{
	arrBackgrounds = new TileEntity ** [TILEMAPSIZE];
	for (int i = 0; i < TILEMAPSIZE; i++)
	{
		arrBackgrounds[i] = new TileEntity* [TILEMAPSIZE];
	}

	this->mapRef = tileRef;//for pixel cheeck
	for (int Y = 0; Y < TILEMAPSIZE; Y++)
	{
		for (int X = 0; X < TILEMAPSIZE; X++)
		{
			if (this->mapRef.getPixel(X, Y) == sf::Color::Color(55, 193, 25))
			{
				TileEntity * wall = new TileEntity("wall01.png");
				wall->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = wall;
				
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 0, 0))
			{
				TileEntity* wall = new TileEntity("floor01.png");
				wall->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = wall;
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
			if (this->mapRef.getPixel(X, Y) == sf::Color::Color(55, 193, 25))
			{
				delete arrBackgrounds[X][Y];
				
			}
		}
	}

	for (int i = 0; i < TILEMAPSIZE; i++)
	{
		
		delete arrBackgrounds[i];
	}
	delete[] arrBackgrounds;
	
}

void TileMap::renderTileMap(sf::RenderWindow & targetWindow)
{
	for (int Y = 0; Y < TILEMAPSIZE; Y++)
	{
		for (int X = 0; X < TILEMAPSIZE; X++)
		{
			if (this->mapRef.getPixel(X, Y) == sf::Color::Color(55, 193, 25))
			{
				targetWindow.draw(*this->arrBackgrounds[X][Y]);
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 0, 0))
			{
				targetWindow.draw(*this->arrBackgrounds[X][Y]);
			}
		}
	}

}
