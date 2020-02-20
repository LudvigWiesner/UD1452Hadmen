#include "TileEntity.h"

TileEntity::TileEntity() : Clickable()
{
	this->collision = false;
}

TileEntity::TileEntity(const int index, ResHandler *resourceHandler) : Clickable(index, resourceHandler)
{
	this->collision = false;
}

void TileEntity::setCollision(const bool collision)
{
	this->collision = collision;
}
