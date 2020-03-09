#pragma once
#ifndef RESOURCETILE_H
#define RESOURCETILE_H
#include "TileEntity.h"
#include <ctime>

class ResourceTile : public TileEntity
{
private:
	std::string name;
public:
	ResourceTile(const int index, ResHandler *resourceHandler, std::string name, float x, float y);

	int getResource()const;
	std::string getName()const;
};
#endif // !RESOURCETILE_H
