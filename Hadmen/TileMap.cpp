#include "TileMap.h"
#include "iostream"

TileMap::TileMap(sf::Image& tileRef, ResHandler* resourceHandler)
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
				TileEntity* tile = new TileEntity(7, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(146, 146, 146))
			{
				TileEntity* tile = new TileEntity(0, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 0, 0))
			{
				TileEntity* tile = new TileEntity(1, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(03, 00, 148))
			{
				TileEntity* tile = new TileEntity(8, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(19, 19, 19))
			{
				TileEntity* tile = new TileEntity(2, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;
			}
			else if (this->mapRef.getPixel(X, Y) == sf::Color::Color(0, 148, 0))
			{
				TileEntity* tile = new TileEntity(14, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;
			}
			else
			{
				TileEntity* tile = new TileEntity(6, resourceHandler);
				tile->setCoordinates(X * 50.0f, Y * 50.0f);
				arrBackgrounds[X][Y] = tile;

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
		delete[] arrBackgrounds[Y];
	}
	delete[] arrBackgrounds;
	delete arrBackgrounds;
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
