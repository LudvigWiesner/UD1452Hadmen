#include <iostream>
#include "List.h"
#include "Item.h"

using namespace std;

int main()
{
	List<Item> playerInventory;

	Item item1("Johan");
	Item item2("Adam");

	playerInventory.insertAt(playerInventory.length(), item1);
	playerInventory.insertAt(playerInventory.length(), item2);

	cout << playerInventory.getAt(1).getName() << endl;
	cout << playerInventory.getAt(0).getName() << endl;
	cout << playerInventory.length() << endl;

	getchar();
	return 0;
}