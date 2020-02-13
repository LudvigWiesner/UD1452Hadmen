#pragma once
#ifndef RESOURCETILE_H
#define RESOURCETILE_H
#include <string>
#include <ctime>

class ResourceTile
{
private:
	std::string name;
public:
	ResourceTile(std::string name);

	int getResource()const;
};
#endif // !RESOURCETILE_H
