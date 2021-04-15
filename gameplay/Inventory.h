/*
 * Inventory.h
 *
 *  Created on: Dec 2, 2020
 *      Author: Domen
 */

#ifndef GAMEPLAY_INVENTORY_H_
#define GAMEPLAY_INVENTORY_H_

#include "../game.h"

class GameItemList;

class Inventory {

private:
	std::vector<unsigned char> items;

public:
	Inventory();
	void addItem(unsigned int item_index, unsigned char ammount = 1);
	void removeItem(unsigned int item_index, unsigned char ammount = 1);
	void removeAllItems(unsigned int item_index);
	bool hasItem(unsigned int item_index);
	bool hasItems(unsigned int item_index, unsigned char ammount);
	unsigned char getItemNumber(unsigned int item_index);
	unsigned int getItemInInventory(unsigned int index);

	friend class GameItemList;

};

#endif /* GAMEPLAY_INVENTORY_H_ */
