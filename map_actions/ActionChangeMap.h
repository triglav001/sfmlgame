/*
 * ActionChangeMap.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONCHANGEMAP_H_
#define MAP_ACTIONS_ACTIONCHANGEMAP_H_

#include "MapAction.h"

class ActionChangeMap : public MapAction {

protected:
	std::string mapchange;
	int player_x;
	int player_y;

public:
	ActionChangeMap(std::string mapname, int pX, int pY);
	virtual bool update(sf::Time delta);

};

#endif /* MAP_ACTIONS_ACTIONCHANGEMAP_H_ */
