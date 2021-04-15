/*
 * MapActionList.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_MAPACTIONLIST_H_
#define MAP_ACTIONS_MAPACTIONLIST_H_

#include "MapAction.h"

class MapActionList : public MapAction {
protected:
	unsigned int cnt = 0;
	std::vector<MapAction*> actions;

public:

	virtual void draw();
	virtual bool update(sf::Time delta);
	virtual void handleInput(sf::Keyboard::Key key);
	virtual void reset();

	virtual void setReferenceScene(SceneMap* _ref);

	MapActionList(std::vector<MapAction*> _actions);
	virtual ~MapActionList();
};

#endif /* MAP_ACTIONS_MAPACTIONLIST_H_ */
