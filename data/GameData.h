/*
 * GameData.h
 *
 *  Created on: Dec 29, 2020
 *      Author: Domen
 */

#ifndef DATA_GAMEDATA_H_
#define DATA_GAMEDATA_H_

#include "../game.h"
#include "../gameplay/Inventory.h"

class MapAction;

struct GameData {
	std::map<std::string, MapAction*> global_actions;
	Inventory player_inventory;
	bool menuEnabled = true;

	// Globals
	static const int MHP_LEVEL_INCREASE = 133;
	static const int MEP_LEVEL_INCREASE = 17;
	static const int ATK_LEVEL_INCREASE = 5;
	static const int DEF_LEVEL_INCREASE = 3;
	static const int MAT_LEVEL_INCREASE = 6;
	static const int MDF_LEVEL_INCREASE = 6;

	static const unsigned int XP_TO_LEVEL_2 = 100;
	static const unsigned int XP_TO_LEVEL_255 = 1000000000;
};

extern GameData game_data;

#endif /* DATA_GAMEDATA_H_ */
