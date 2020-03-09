#pragma once
#ifndef WATERTILE_H
#define WATERTILE_H
#include "TileEntity.h"
#include "ResourceTile.h"
#include <string>

class WaterTile : public TileEntity, ResourceTile
{
private:
public:
	WaterTile();
};
#endif // !WATERTILE_H
