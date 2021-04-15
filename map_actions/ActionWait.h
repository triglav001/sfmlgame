/*
 * ActionWait.h
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONWAIT_H_
#define MAP_ACTIONS_ACTIONWAIT_H_

#include "MapAction.h"

class ActionWait : public MapAction {
protected:
	sf::Time wait_for;

public:
	ActionWait(sf::Time _wait_for);
	virtual bool update(sf::Time delta);
};

#endif /* MAP_ACTIONS_ACTIONWAIT_H_ */
