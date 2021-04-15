/*
 * ActionWait.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#include "ActionWait.h"

ActionWait::ActionWait(sf::Time _wait_for)
	: wait_for(_wait_for) {
}

bool ActionWait::update(sf::Time delta) {
	internal_cnt += delta;
	if (internal_cnt >= wait_for) {
		is_done = true;
		return true;
	}
	return false;
}
