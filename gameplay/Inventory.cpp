/*
 * Inventory.cpp
 *
 *  Created on: Dec 2, 2020
 *      Author: Domen
 */

#include "Inventory.h"

Inventory::Inventory() {
	// TODO init vector
	items = std::vector<unsigned char>(game_items.size(), 0);
}

void Inventory::addItem(unsigned int item_index, unsigned char ammount) {
	if (items.size() <= item_index)
		return;
	if (items[item_index] > 255 - ammount)
		items[item_index] = 255;
	else
		items[item_index] += ammount;
}

bool Inventory::hasItem(unsigned int item_index) {
	if (items.size() <= item_index)
		return false;
	return (items[item_index] != 0);
}

bool Inventory::hasItems(unsigned int item_index, unsigned char ammount) {
	if (items.size() <= item_index)
		return false;
	return (items[item_index] >= ammount);
}

void Inventory::removeItem(unsigned int item_index, unsigned char ammount) {
	if (items.size() <= item_index)
		return;
	if (ammount >= items[item_index])
		items[item_index] = 0;
	else
		items[item_index] -= ammount;
}

void Inventory::removeAllItems(unsigned int item_index) {
	if (items.size() <= item_index)
		return;
	items[item_index] = 0;
}

unsigned char Inventory::getItemNumber(unsigned int item_index) {
	if (items.size() <= item_index)
		return 0;
	return items[item_index];
}

unsigned int Inventory::getItemInInventory(unsigned int index) {
	unsigned int cnt = 0;
	for (unsigned int u=0; u<items.size(); u++) {
		if (items[u] == 0)
			continue;
		cnt++;
		if (cnt == index)
			return u;
	}
	return 0;
}
