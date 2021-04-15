/*
 * MapActionList.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: Domen
 */

#include "MapActionList.h"
#include "MapAction.h"

void MapActionList::draw() {
	if (is_done)
		return;
	actions[cnt]->draw();
}

bool MapActionList::update(sf::Time delta) {
	if (is_done)
		return true;
	bool result = actions[cnt]->update(delta);
	if (result) {
		cnt++;
		if (cnt >= actions.size()) {
			is_done = true;
			return true;
		}
	}
	return false;
}

void MapActionList::reset() {
	for (MapAction* action : actions) {
		action->reset();
	}
	cnt = 0;
	is_done = false;
}

MapActionList::MapActionList(std::vector<MapAction*> _actions)
	: actions(_actions) {
}

void MapActionList::setReferenceScene(SceneMap* _ref) {
	scene_ref = _ref;
	for (MapAction* a : actions) {
		a->setReferenceScene(_ref);
	}
}

void MapActionList::handleInput(sf::Keyboard::Key key) {
	if (is_done)
		return;
	actions[cnt]->handleInput(key);
}

MapActionList::~MapActionList() {
}
