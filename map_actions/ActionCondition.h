/*
 * ActionCondition.h
 *
 *  Created on: Dec 4, 2020
 *      Author: Domen
 */

#ifndef MAP_ACTIONS_ACTIONCONDITION_H_
#define MAP_ACTIONS_ACTIONCONDITION_H_

#include "MapAction.h"

enum ConditionCompareType {
	TypeAND, TypeOR
};

class ActionCondition: MapAction {

protected:
	std::vector<bool*> conditions;
	MapAction* ifTrue;
	MapAction* ifFalse;
	int value = 0;
	ConditionCompareType compare_type;

public:
	ActionCondition(std::vector<bool*> cond, MapAction* aTrue = NULL,
			MapAction* aFalse = NULL, ConditionCompareType comp_type =
					ConditionCompareType::TypeAND);
	virtual bool update(sf::Time delta);
	virtual void draw();
	virtual void handleInput(sf::Keyboard::Key key);
	virtual void reset();

};

#endif /* MAP_ACTIONS_ACTIONCONDITION_H_ */
