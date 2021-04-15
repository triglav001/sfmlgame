/*
 * ItemList.cpp
 *
 *  Created on: Dec 2, 2020
 *      Author: Domen
 */

#include "GameItemList.h"
#include "../gameplay/Inventory.h"

GameItemList::GameItemList(Inventory* inv) {
	inventory = inv;
	draw_icons = true;
	refresh();
}

void GameItemList::refresh() {
	list_items.clear();
	BasicListItem bli;
	bli.on_select = NULL;
	bli.spriteset_id = 0;
	char buffer[512];
	for (unsigned int u=0; u<inventory->items.size(); u++) {
		if (inventory->items[u] == 0)
			continue;
		sprintf(buffer, "%i x %s", (int) inventory->items[u], game_items[u].item_name.c_str());
		bli.item_name = std::string(buffer);
		bli.sprite_id = game_items[u].item_tex;
		list_items.push_back(bli);
	}
}
