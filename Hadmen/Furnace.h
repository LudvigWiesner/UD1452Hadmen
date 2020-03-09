#pragma once
#include "constructions.h"

class Furnace : public Construction
{
private:
	int coal;
	int counter;
	int updateTime;
protected:


public:
	Furnace(const int index, ResHandler* resourceHandler);

	void addCoal(PlayerCharacter* pc);

	void proccessCoal();

	void updateFurnace(ResHandler* resourceHandler);

	int getCoalAmount() const;

};