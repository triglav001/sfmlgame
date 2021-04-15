/*
 * ActionCondition.cpp
 *
 *  Created on: Dec 4, 2020
 *      Author: Domen
 */

#include "ActionCondition.h"

ActionCondition::ActionCondition(std::vector<bool*> cond, MapAction* aTrue,
		MapAction* aFalse, ConditionCompareType comp_type) {
	conditions = cond;
	ifTrue = aTrue;
	ifFalse = aFalse;
	compare_type = comp_type;
}

bool ActionCondition::update(sf::Time delta) {
	if (value == 1 && ifTrue != NULL && ifTrue->update(delta)) {
		is_done = true;
		return true;
	}
	else if (value == 2 && ifFalse != NULL && ifFalse->update(delta)) {
		is_done = true;
		return true;
	}
	else {
		if (compare_type == ConditionCompareType::TypeAND) {
			value = 1;
			for (bool* v : conditions) {
				if (!(*v)) {
					value = 2;
					break;
				}
			}
		}
		else if (compare_type == ConditionCompareType::TypeOR) {
			value = 2;
			for (bool* v : conditions) {
				if ((*v)) {
					value = 1;
					break;
				}
			}
		}
		return update(delta);
	}
}

void ActionCondition::draw() {
	if (value == 1 && ifTrue != NULL)
		ifTrue->draw();
	if (value == 2 && ifFalse != NULL)
		ifFalse->draw();
}

void ActionCondition::handleInput(sf::Keyboard::Key key) {
	if (value == 1 && ifTrue != NULL)
		ifTrue->handleInput(key);
	if (value == 2 && ifFalse != NULL)
		ifFalse->handleInput(key);
}

void ActionCondition::reset() {
	value = 0;
	if (ifTrue != NULL)
		ifTrue->reset();
	if (ifFalse != NULL)
		ifFalse->reset();
}
