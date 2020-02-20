#pragma once
#include "Clickable.h"

class TileEntity : public Clickable
{
private:
	bool collision;
public:
	TileEntity();
	TileEntity(const int index, ResHandler *resourceHandler);

	void setCollision(const bool collision);
};