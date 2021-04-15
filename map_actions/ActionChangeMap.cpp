/*
 * ActionChangeMap.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: Domen
 */

#include "ActionChangeMap.h"
#include "../map/SceneMap.h"
#include "../map/GameMap.h"

ActionChangeMap::ActionChangeMap(std::string mapname, int pX, int pY) {
	mapchange = mapname;
	player_x = pX;
	player_y = pY;
}

bool ActionChangeMap::update(sf::Time delta) {
	scene_ref->setMap(maps[mapchange], player_x, player_y);
	is_done = true;
	return true;
}
