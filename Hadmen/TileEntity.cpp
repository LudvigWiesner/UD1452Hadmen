#include "TileEntity.h"

TileEntity::TileEntity() : Clickable()
{
	this->collision = false;
}

TileEntity::TileEntity(const int index, ResHandler *resourceHandler, float x, float y) : Clickable(index, resourceHandler,x,y)
{
	this->collision = false;
}

void TileEntity::setCollision(const bool collision)
{
	this->collision = collision;
}
