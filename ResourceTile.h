#pragma once
#ifndef RESOURCETILE_H
#define RESOURCETILE_H
#include "TileEntity.h"
#include <ctime>

class ResourceTile : public TileEntity
{
private:
	std::string name;
	bool containsResource;
public:
	ResourceTile(const int index, ResHandler *resourceHandler, std::string name, float x, float y);

	bool getIfHasResource()const;
	int getResource()const;
	std::string getName()const;
	void setName(std::string name);
	void switchTexture(ResHandler* resourceHandler);
};
#endif // !RESOURCETILE_H
