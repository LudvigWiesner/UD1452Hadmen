#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item
{
private:
	std::string name;
public:
	Item();
	Item(std::string name);

	std::string getName();
};
#endif // !Item
