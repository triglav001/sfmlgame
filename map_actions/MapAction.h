/*
 * MapAction.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_MAPACTION_H_
#define MAP_ACTIONS_MAPACTION_H_

#include "../game.h"

class SceneMap;

// Base class for map-related events
class MapAction {
protected:
	bool is_done = false;
	sf::Time internal_cnt = sf::Time::Zero;
	SceneMap* scene_ref = NULL;

public:
	bool isDone();
	virtual void setReferenceScene(SceneMap* _ref);

	virtual void draw();
	virtual bool update(sf::Time delta);
	virtual void handleInput(sf::Keyboard::Key key);

	virtual void reset();
	virtual ~MapAction();
};

#endif /* MAP_ACTIONS_MAPACTION_H_ */
